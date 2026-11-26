extern "C" {
#pragma readonly_strings on
#pragma dont_inline on
#pragma bool off
#include "types.h"

#include "thp_player.h"
#include "dvd.h"
#include "vi.h"
extern void ReadThreadCancel(void);
extern void VideoDecodeThreadCancel(void);
extern void AudioDecodeThreadCancel(void);
extern void *PopUsedTextureSet(void);
#define ALIGN_NEXT(a, n) (((a) + (n) - 1) & ~((n) - 1))
extern void DCInvalidateRange(void *, u32);
extern void InitAllMessageQueue(void);
extern BOOL WaitUntilPrepare(void);
extern BOOL CreateReadThread(OSPriority);
extern BOOL CreateVideoDecodeThread(OSPriority, void *);
extern BOOL CreateAudioDecodeThread(OSPriority, void *);
extern void ReadThreadStart(void);
extern void VideoDecodeThreadStart(void);
extern void AudioDecodeThreadStart(void);
void PlayControl(u32);
#include "runtime_string.h"
extern BOOL ProperTimingForStart(void);
extern BOOL ProperTimingForGettingNextFrame(void);
extern void PushUsedTextureSet(void *);

BOOL THPPlayerOpen(const char *fileName, BOOL onMemory);
s32 THPPlayerCalcNeedMemory(void);
BOOL THPPlayerSetBuffer(u8 *buffer);
BOOL THPPlayerPrepare(s32 position, s32 flag);
void THPPlayerStop(void);
void PlayControl(u32 retraceCount);
s32 THPPlayerDrawCurrentFrame(struct GXRenderModeObj *rmode, u32 x, u32 y, u32 polygonW, u32 polygonH);
u32 THPPlayerAudioOutput(s16 *destination, u32 sample, s32 volume);
#pragma force_active on
static u32 WorkBuffer[16];
static OSMessageQueue PrepareReadyQueue;
static OSMessageQueue UsedTextureSetQueue;
static OSMessage UsedTextureSetMessage[3];
THPPlayer ActivePlayer __attribute__((aligned(16))) ;
static BOOL Initialized;
static void *PrepareReadyMessage;
static void (*OldVIPostCallback)(u32);
#pragma force_active off
BOOL THPPlayerOpen(const char *fileName, BOOL onMemory)
{
    s32 offset;
    u32 i;
    if (!Initialized)
        return 0;
    if (ActivePlayer.open)
        return 0;
    memset(&ActivePlayer.videoInfo, 0, sizeof(THPVideoInfo));
    memset(&ActivePlayer.audioInfo, 0, sizeof(THPAudioInfo));
    if (!DVDOpen((char *)fileName, &ActivePlayer.fileInfo))
        return 0;
    if (DVDReadPrio(&ActivePlayer.fileInfo, WorkBuffer, 64, 0, 2) < 0) {
        DVDClose(&ActivePlayer.fileInfo);
        return 0;
    }
    memcpy(&ActivePlayer.header, WorkBuffer, sizeof(THPHeader));
    if (strcmp((char *)ActivePlayer.header.magic, "THP") != 0) {
        DVDClose(&ActivePlayer.fileInfo);
        return 0;
    }
    if (ActivePlayer.header.version != 0x00010000) {
        DVDClose(&ActivePlayer.fileInfo);
        return 0;
    }
    offset = ActivePlayer.header.compInfoDataOffsets;
    if (DVDReadPrio(&ActivePlayer.fileInfo, WorkBuffer, 32, offset, 2) < 0) {
        DVDClose(&ActivePlayer.fileInfo);
        return 0;
    }
    memcpy(&ActivePlayer.compInfo, WorkBuffer, sizeof(THPFrameCompInfo));
    ActivePlayer.audioExist = 0;
    offset += sizeof(THPFrameCompInfo);
    for (i = 0; i < ActivePlayer.compInfo.numComponents; i++) {
        switch (ActivePlayer.compInfo.frameComp[i]) {
        case 0:
            if (DVDReadPrio(&ActivePlayer.fileInfo, WorkBuffer, 32, offset, 2) < 0) {
                DVDClose(&ActivePlayer.fileInfo);
                return 0;
            }
            memcpy(&ActivePlayer.videoInfo, WorkBuffer, sizeof(THPVideoInfo));
            offset += sizeof(THPVideoInfo);
            break;
        case 1:
            if (DVDReadPrio(&ActivePlayer.fileInfo, WorkBuffer, 32, offset, 2) < 0) {
                DVDClose(&ActivePlayer.fileInfo);
                return 0;
            }
            memcpy(&ActivePlayer.audioInfo, WorkBuffer, sizeof(THPAudioInfo));
            ActivePlayer.audioExist = 1;
            offset += sizeof(THPAudioInfo);
            break;
        default:
            return 0;
        }
    }
    ActivePlayer.state = ActivePlayer.internalState = 0;
    ActivePlayer.playFlag = 0;
    ActivePlayer.onMemory = onMemory;
    ActivePlayer.open = 1;
    return 1;
}

s32 THPPlayerCalcNeedMemory(void)
{
    s32 size;
    if (ActivePlayer.open) {
        if (ActivePlayer.onMemory)
            size = ALIGN_NEXT(ActivePlayer.header.movieDataSize, 32);
        else
            size = ALIGN_NEXT(ActivePlayer.header.bufsize, 32) * 10;
        size += ALIGN_NEXT(ActivePlayer.videoInfo.xSize * ActivePlayer.videoInfo.ySize, 32) * 3;
        size += ALIGN_NEXT(ActivePlayer.videoInfo.xSize * ActivePlayer.videoInfo.ySize / 4, 32) * 3;
        size += ALIGN_NEXT(ActivePlayer.videoInfo.xSize * ActivePlayer.videoInfo.ySize / 4, 32) * 3;
        if (ActivePlayer.audioExist)
            size += ALIGN_NEXT(ActivePlayer.header.audioMaxSamples * 4, 32) * 3;
        size += 0x1000;
        return size;
    }
    return 0;
}

BOOL THPPlayerSetBuffer(u8 *buffer)
{
    u8 *ptr;
    u32 i;
    u32 ySize;
    u32 uvSize;
    if (ActivePlayer.open && !ActivePlayer.state) {
        ptr = buffer;
        if (ActivePlayer.onMemory) {
            ActivePlayer.movieData = ptr;
            ptr += ActivePlayer.header.movieDataSize;
        } else {
            for (i = 0; i < 10; i++) {
                ActivePlayer.readBuffer[i].ptr = ptr;
                ptr += ALIGN_NEXT(ActivePlayer.header.bufsize, 32);
            }
        }
        ySize = ALIGN_NEXT(ActivePlayer.videoInfo.xSize * ActivePlayer.videoInfo.ySize, 32);
        uvSize = ALIGN_NEXT(ActivePlayer.videoInfo.xSize * ActivePlayer.videoInfo.ySize / 4, 32);
        for (i = 0; i < 3; i++) {
            ActivePlayer.textureSet[i].ytexture = ptr;
            DCInvalidateRange(ptr, ySize);
            ptr += ySize;
            ActivePlayer.textureSet[i].utexture = ptr;
            DCInvalidateRange(ptr, uvSize);
            ptr += uvSize;
            ActivePlayer.textureSet[i].vtexture = ptr;
            DCInvalidateRange(ptr, uvSize);
            ptr += uvSize;
        }
        if (ActivePlayer.audioExist) {
            for (i = 0; i < 3; i++) {
                ActivePlayer.audioBuffer[i].buffer = (s16 *)ptr;
                ActivePlayer.audioBuffer[i].curPtr = (s16 *)ptr;
                ActivePlayer.audioBuffer[i].validSample = 0;
                ptr += ALIGN_NEXT(ActivePlayer.header.audioMaxSamples * 4, 32);
            }
        }
        ActivePlayer.thpWork = ptr;
        return 1;
    }
    return 0;
}

BOOL THPPlayerPrepare(s32 position, s32 flag)
{
    s32 offset;
    u8 *ptr;
    if (ActivePlayer.open && !ActivePlayer.state) {
        if (position > 0) {
            if (!ActivePlayer.header.offsetDataOffsets)
                return 0;
            if (ActivePlayer.header.numFrames > position) {
                offset = ActivePlayer.header.offsetDataOffsets + (position - 1) * 4;
                if (DVDReadPrio(&ActivePlayer.fileInfo, WorkBuffer, 32, offset, 2) < 0)
                    return 0;
                ActivePlayer.initOffset = ActivePlayer.header.movieDataOffsets + WorkBuffer[0];
                ActivePlayer.initReadFrame = position;
                ActivePlayer.initReadSize = WorkBuffer[1] - WorkBuffer[0];
            } else
                return 0;
        } else {
            ActivePlayer.initOffset = ActivePlayer.header.movieDataOffsets;
            ActivePlayer.initReadSize = ActivePlayer.header.firstFrameSize;
            ActivePlayer.initReadFrame = position;
        }
        ActivePlayer.playFlag = flag;
        ActivePlayer.videoDecodeCount = 0;
        if (ActivePlayer.onMemory) {
            if (DVDReadPrio(&ActivePlayer.fileInfo, ActivePlayer.movieData, ActivePlayer.header.movieDataSize, ActivePlayer.header.movieDataOffsets, 2) < 0)
                return 0;
            ptr = ActivePlayer.movieData + ActivePlayer.initOffset - ActivePlayer.header.movieDataOffsets;
            CreateVideoDecodeThread(20, ptr);
            if (ActivePlayer.audioExist)
                CreateAudioDecodeThread(12, ptr);
        } else {
            CreateVideoDecodeThread(20, 0);
            if (ActivePlayer.audioExist)
                CreateAudioDecodeThread(12, 0);
            CreateReadThread(8);
        }
        InitAllMessageQueue();
        VideoDecodeThreadStart();
        if (ActivePlayer.audioExist)
            AudioDecodeThreadStart();
        if (!ActivePlayer.onMemory)
            ReadThreadStart();
        if (!WaitUntilPrepare())
            return 0;
        ActivePlayer.state = 1;
        ActivePlayer.internalState = 0;
        ActivePlayer.dispTextureSet = 0;
        ActivePlayer.playAudioBuffer = 0;
        ActivePlayer.curVideoNumber = 0;
        ActivePlayer.curAudioNumber = 0;
        OldVIPostCallback = VISetPostRetraceCallback(PlayControl);
        return 1;
    }
    return 0;
}

void THPPlayerStop(void)
{
    void *msg;
    if (ActivePlayer.open && ActivePlayer.state) {
        ActivePlayer.state = ActivePlayer.internalState = 0;
        VISetPostRetraceCallback(OldVIPostCallback);
        if (!ActivePlayer.onMemory) {
            DVDCancel((DVDCommandBlock *)&ActivePlayer.fileInfo);
            ReadThreadCancel();
        }
        VideoDecodeThreadCancel();
        if (ActivePlayer.audioExist)
            AudioDecodeThreadCancel();
        do {
            msg = PopUsedTextureSet();
        } while (msg != (void *)0);
        ActivePlayer.dvdError = 0;
        ActivePlayer.videoError = 0;
    }
}

void PlayControl(u32 retraceCount)
{
    THPTextureSet *textureSet;
    s32 diff;
    u32 frame;
    if (OldVIPostCallback)
        OldVIPostCallback(retraceCount);
    textureSet = (THPTextureSet *)-1;
    if (ActivePlayer.open && ActivePlayer.state == 2) {
        if (ActivePlayer.dvdError || ActivePlayer.videoError) {
            ActivePlayer.state = ActivePlayer.internalState = 5;
            return;
        }
        if (ActivePlayer.retaceCount == 0 && ActivePlayer.internalState == 0)
            ActivePlayer.internalState = 2;
        ActivePlayer.retaceCount++;
        if (ActivePlayer.internalState == 0 || ActivePlayer.internalState == 4) {
            if (ProperTimingForStart()) {
                if (ActivePlayer.audioExist) {
                    diff = ActivePlayer.curVideoNumber - ActivePlayer.curAudioNumber;
                    if (diff <= 1) {
                        textureSet = (THPTextureSet *)PopDecodedTextureSet(0);
                        if (ActivePlayer.videoDecodeCount > diff)
                            ActivePlayer.videoDecodeCount--;
                    } else {
                        ActivePlayer.internalState = 2;
                    }
                } else {
                    textureSet = (THPTextureSet *)PopDecodedTextureSet(0);
                    ActivePlayer.internalState = 2;
                }
            } else {
                ActivePlayer.retaceCount = -1;
            }
        } else if (ProperTimingForGettingNextFrame()) {
            if (ActivePlayer.audioExist) {
                diff = ActivePlayer.curVideoNumber - ActivePlayer.curAudioNumber;
                if (diff <= 1) {
                    textureSet = (THPTextureSet *)PopDecodedTextureSet(0);
                    if (ActivePlayer.videoDecodeCount > diff)
                        ActivePlayer.videoDecodeCount--;
                }
            } else {
                textureSet = (THPTextureSet *)PopDecodedTextureSet(0);
            }
        }
        if (textureSet != 0 && textureSet != (THPTextureSet *)-1) {
            ActivePlayer.curVideoNumber = textureSet->frameNumber;
            if (ActivePlayer.dispTextureSet)
                PushUsedTextureSet(ActivePlayer.dispTextureSet);
            ActivePlayer.dispTextureSet = textureSet;
        }
        if (!(ActivePlayer.playFlag & 1)) {
            if (ActivePlayer.audioExist) {
                frame = (ActivePlayer.curAudioNumber + ActivePlayer.initReadFrame) % ActivePlayer.header.numFrames;
                if (frame == ActivePlayer.header.numFrames - 1 && ActivePlayer.playAudioBuffer == (THPAudioBuffer *)0) {
                    frame = (ActivePlayer.curVideoNumber + ActivePlayer.initReadFrame) % ActivePlayer.header.numFrames;
                    if (frame == ActivePlayer.header.numFrames - 1 && textureSet == (THPTextureSet *)0)
                        ActivePlayer.state = ActivePlayer.internalState = 3;
                }
            } else {
                frame = (ActivePlayer.curVideoNumber + ActivePlayer.initReadFrame) % ActivePlayer.header.numFrames;
                if (frame == ActivePlayer.header.numFrames - 1 && textureSet == (THPTextureSet *)0)
                    ActivePlayer.state = ActivePlayer.internalState = 3;
            }
        }
    }
}

s32 THPPlayerDrawCurrentFrame(struct GXRenderModeObj *rmode, u32 x, u32 y, u32 polygonW, u32 polygonH)
{
    s32 result;
    if (ActivePlayer.open && ActivePlayer.state && ActivePlayer.dispTextureSet) {
        THPGXYuv2RgbSetup(rmode);
        THPGXYuv2RgbDraw(ActivePlayer.dispTextureSet->ytexture, ActivePlayer.dispTextureSet->utexture,
                         ActivePlayer.dispTextureSet->vtexture, (s16)x, (s16)y,
                         (s16)ActivePlayer.videoInfo.xSize, (s16)ActivePlayer.videoInfo.ySize,
                         (s16)polygonW, (s16)polygonH);
        THPGXRestore();
        result = (ActivePlayer.dispTextureSet->frameNumber + ActivePlayer.initReadFrame) % ActivePlayer.header.numFrames;
        return result;
    }
    return -1;
}

static u16 VolumeTable[128] = {
    0,     2,     8,     18,    32,    50,    73,    99,    130,   164,   203,   245,
    292,   343,   398,   457,   520,   587,   658,   733,   812,   895,   983,   1074,
    1170,  1269,  1373,  1481,  1592,  1708,  1828,  1952,  2080,  2212,  2348,  2488,
    2632,  2781,  2933,  3090,  3250,  3415,  3583,  3756,  3933,  4114,  4298,  4487,
    4680,  4877,  5079,  5284,  5493,  5706,  5924,  6145,  6371,  6600,  6834,  7072,
    7313,  7559,  7809,  8063,  8321,  8583,  8849,  9119,  9394,  9672,  9954,  10241,
    10531, 10826, 11125, 11427, 11734, 12045, 12360, 12679, 13002, 13329, 13660, 13995,
    14335, 14678, 15025, 15377, 15732, 16092, 16456, 16823, 17195, 17571, 17951, 18335,
    18723, 19115, 19511, 19911, 20316, 20724, 21136, 21553, 21974, 22398, 22827, 23260,
    23696, 24137, 24582, 25031, 25484, 25941, 26402, 26868, 27337, 27810, 28288, 28769,
    29255, 29744, 30238, 30736, 31238, 31744, 32254, 32768};
u32 THPPlayerAudioOutput(s16 *destination, u32 sample, s32 volume)
{
    s32 mix;
    s16 *dest;
    s16 *src;
    u32 i;
    u32 n;
    u16 vol;
    u32 remain;
    u32 total;
    if (volume < 0)
        volume = 0;
    if (volume > 127)
        volume = 127;
    vol = VolumeTable[volume];
    if (ActivePlayer.open && ActivePlayer.internalState == 2 && ActivePlayer.audioExist) {
        remain = sample;
        total = 0;
        dest = destination;
        for (;;) {
            if (ActivePlayer.playAudioBuffer == (THPAudioBuffer *)0) {
                if ((ActivePlayer.playAudioBuffer = (THPAudioBuffer *)PopDecodedAudioBuffer(0)) == (THPAudioBuffer *)0)
                    break;
                ActivePlayer.curAudioNumber = ActivePlayer.playAudioBuffer->frameNumber;
            }
            if (ActivePlayer.playAudioBuffer->validSample == 0)
                continue;
            if (ActivePlayer.playAudioBuffer->validSample >= remain)
                n = remain;
            else
                n = ActivePlayer.playAudioBuffer->validSample;
            src = ActivePlayer.playAudioBuffer->curPtr;
            for (i = 0; i < n * 2; i++) {
                mix = *dest + ((vol * *src) >> 15);
                if (mix < -32767)
                    mix = -32767;
                if (mix > 0x8000)
                    mix = 0x8000;
                *dest = mix;
                dest++;
                src++;
            }
            total += n;
            remain -= n;
            ActivePlayer.playAudioBuffer->validSample -= n;
            ActivePlayer.playAudioBuffer->curPtr = src;
            if (ActivePlayer.playAudioBuffer->validSample == 0) {
                PushFreeAudioBuffer(ActivePlayer.playAudioBuffer);
                ActivePlayer.playAudioBuffer = (THPAudioBuffer *)PopDecodedAudioBuffer(0);
                if (ActivePlayer.playAudioBuffer)
                    ActivePlayer.curAudioNumber = ActivePlayer.playAudioBuffer->frameNumber;
            }
            if (remain == 0)
                break;
        }
        return total;
    }
    return 0;
}

u32 SE_TableList[357] = {
    0xFFFFFFFF, 0x00000140, 0x00000141, 0x00000142, 0x00000143, 0x00000144, 0x00000145, 0x00000146,
    0x00000147, 0x00000148, 0x00000149, 0x0000014A, 0x0000014B, 0x0000014C, 0x0000014D, 0x0000014E,
    0x0000014F, 0x00000150, 0x00000151, 0x00000152, 0x00000153, 0x00000154, 0x00000155, 0x00000156,
    0x00000157, 0x00000158, 0x00000159, 0x0000015A, 0x0000015B, 0x0000015C, 0x0000015D, 0x0000015E,
    0x0000015F, 0x00000160, 0x00000161, 0x00000162, 0x00000163, 0x00000164, 0x00000165, 0x00000166,
    0x00000167, 0x00000168, 0x00000169, 0x0000016A, 0x0000016B, 0x0000016C, 0x0000016D, 0x0000016E,
    0x0000016F, 0x00000170, 0x00000171, 0x00000172, 0x00000173, 0x00000174, 0x00000175, 0x00000176,
    0x00000177, 0x00000178, 0x00000179, 0x0000017A, 0x0000017B, 0x0000017C, 0x0000017D, 0x0000017E,
    0x0000017F, 0x00000180, 0x00000181, 0x00000182, 0x00000183, 0x00000184, 0x00000185, 0x00000186,
    0x00000187, 0x00000188, 0x00000189, 0x0000018A, 0x0000018B, 0x0000018C, 0x0000018D, 0x0000018E,
    0x0000018F, 0x00000190, 0x00000191, 0x00000192, 0x00000193, 0x00000194, 0x00000195, 0x00000196,
    0x00000197, 0x00000198, 0x00000199, 0x0000019A, 0x0000019B, 0x0000019C, 0x0000019D, 0x0000019E,
    0x0000019F, 0x000001A0, 0x000001A1, 0x000001A2, 0x000001A3, 0x000001A4, 0x000001A5, 0x000001A6,
    0x000001A7, 0x000001A8, 0x000001A9, 0x000001AA, 0x000001AB, 0x000001AC, 0x000001AD, 0x000001AE,
    0x000001AF, 0x000001B0, 0x000001B1, 0x000001B2, 0x000001B3, 0x000001B4, 0x000001B5, 0x000001B6,
    0x000001B7, 0x000001B8, 0x000001B9, 0x000001BA, 0x000001BB, 0x000001BC, 0x000001BD, 0x000001BE,
    0x000001BF, 0x000001C0, 0x000001C1, 0x000001C2, 0x000001C3, 0x000001C4, 0x000001C5, 0x000001C6,
    0x000001C7, 0x000001C8, 0x000001C9, 0x000001CA, 0x000001CB, 0x000001CC, 0x000001CD, 0x000001CE,
    0x000001CF, 0x000001D0, 0x000001D1, 0x000001D2, 0x000001D3, 0x000001D4, 0x000001D5, 0x000001D6,
    0x000001D7, 0x000001D8, 0x000001D9, 0x000001DA, 0x000001DB, 0x000001DC, 0x000001DD, 0x000001DE,
    0x000001DF, 0x000001E0, 0x000001E1, 0x000001E2, 0x000001E3, 0x000001E4, 0x000001E5, 0x000001E6,
    0x000001E7, 0x000001E8, 0x000001E9, 0x000001EA, 0x000001EB, 0x000001EC, 0x000001ED, 0x000001EE,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0x000001EF, 0x000001F0, 0x000001F1, 0x000001F2, 0x000001F3, 0x000001F4, 0x000001F5, 0x000001F6,
    0x000001F7, 0x000001F8, 0x000001F9, 0x000001FA, 0x000001FB, 0x000001FC, 0x000001FD, 0x000001FE,
    0x000001FF, 0x00000200, 0x00000201, 0x00000202, 0x00000203, 0x00000204, 0x00000205, 0x00000206,
    0x00000207, 0x00000208, 0x00000209, 0x0000020A, 0x0000020B, 0x0000020C, 0x0000020D, 0x0000020E,
    0x0000020F, 0x00000210, 0x00000211, 0x00000212, 0x00000213, 0x00000214, 0x00000215, 0x00000216,
    0x00000217, 0x00000218, 0x00000219, 0x0000021A, 0x0000021B, 0x0000021C, 0x0000021D, 0x0000021E,
    0x0000021F, 0x00000220, 0x00000221, 0x00000222, 0x00000223, 0x00000224, 0x00000225, 0x00000226,
    0x00000227, 0x00000228, 0x00000229, 0x0000022A, 0x0000022B, 0x0000022C, 0x0000022D, 0x0000022E,
    0x0000022F, 0x00000230, 0x00000231, 0x00000232, 0x00000233, 0x00000234, 0x00000235, 0x00000236,
    0x00000237, 0x00000238, 0x00000239, 0x0000023A, 0x0000023B, 0x0000023C, 0x0000023D, 0x0000023E,
    0x0000023F, 0x00000240, 0x00000241, 0x00000242, 0x00000243, 0x00000244, 0x00000245, 0x00000246,
    0x00000247, 0x00000248, 0x0000013F, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
    0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF
};
}
