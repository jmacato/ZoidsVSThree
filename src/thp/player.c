/* Reference: https://github.com/doldecomp/sms/blob/main/libs/THPPlayer/src/THPPlayer.c.
 */
#include "thp_player.h"
#include "initialize.h"
#include "runtime_string.h"
#include "gx_framebuffer.h"
#include "vi.h"
#include "dvd.h"
#define ARRAY_COUNT(a) (sizeof(a) / sizeof((a)[0]))
#define ALIGN_NEXT(a, n) (((a) + (n) - 1) & ~((n) - 1))
static u32 WorkBuffer[16];
static OSMessageQueue PrepareReadyQueue;
static OSMessageQueue UsedTextureSetQueue;
static OSMessage UsedTextureSetMessage[3];
THPPlayer ActivePlayer;
static BOOL Initialized;
static void *PrepareReadyMessage;
static void (*OldVIPostCallback)(u32);
extern int THPInit(void);


static void *PopUsedTextureSet(void);
static void PushUsedTextureSet(OSMessage);
BOOL THPPlayerInit(void)
{
    memset(&ActivePlayer, 0, sizeof(THPPlayer));
    LCEnable();
    OSInitMessageQueue(&UsedTextureSetQueue, UsedTextureSetMessage, 3);
    if (THPInit()) {
        Initialized = TRUE;
        return TRUE;
    }
    return FALSE;
}
void THPPlayerQuit(void)
{
    LCDisable();
    Initialized = FALSE;
}





static void InitAllMessageQueue(void)
{
    s32 i;
    THPReadBuffer *readBuffer;
    THPTextureSet *textureSet;
    THPAudioBuffer *audioBuffer;

    if (!ActivePlayer.onMemory) {
        for (i = 0; i < 10; i++) {
            readBuffer = &ActivePlayer.readBuffer[i];
            PushFreeReadBuffer(readBuffer);
        }
    }
    for (i = 0; i < 3; i++) {
        textureSet = &ActivePlayer.textureSet[i];
        PushFreeTextureSet(textureSet);
    }
    if (ActivePlayer.audioExist) {
        for (i = 0; i < 3; i++) {
            audioBuffer = &ActivePlayer.audioBuffer[i];
            PushFreeAudioBuffer(audioBuffer);
        }
    }
    OSInitMessageQueue(&PrepareReadyQueue, &PrepareReadyMessage, 1);
}

static BOOL WaitUntilPrepare()
{
    OSMessage msg;

    OSReceiveMessage(&PrepareReadyQueue, &msg, OS_MESSAGE_BLOCK);

    if ((BOOL)(s32)msg) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void PrepareReady(BOOL msg)
{
    OSSendMessage(&PrepareReadyQueue, (OSMessage)(s32)msg, OS_MESSAGE_BLOCK);
}

BOOL THPPlayerGetVideoInfo(THPVideoInfo *videoInfo)
{
    if (ActivePlayer.open) {
        memcpy(videoInfo, &ActivePlayer.videoInfo, sizeof(THPVideoInfo));
        return TRUE;
    }

    return FALSE;
}

s32 THPPlayerGetState()
{
    return ActivePlayer.state;
}



static void PushUsedTextureSet(OSMessage msg)
{
    OSSendMessage(&UsedTextureSetQueue, msg, OS_MESSAGE_NOBLOCK);
}

static OSMessage PopUsedTextureSet()
{
    OSMessage msg;
    if (OSReceiveMessage(&UsedTextureSetQueue, &msg, OS_MESSAGE_NOBLOCK) == 1)
        return msg;

    return NULL;
}

extern void ReadThreadCancel(void);
extern void VideoDecodeThreadCancel(void);
extern void AudioDecodeThreadCancel(void);
static BOOL ProperTimingForStart(void);
static BOOL ProperTimingForGettingNextFrame(void);


BOOL THPPlayerClose()
{
    if (ActivePlayer.open && ActivePlayer.state == THP_PLAYER_STOP) {
        ActivePlayer.open = FALSE;
        DVDClose(&ActivePlayer.fileInfo);
        return TRUE;
    }

    return FALSE;
}

BOOL THPPlayerPlay()
{
    if (ActivePlayer.open && (ActivePlayer.state == THP_PLAYER_PREPARE || ActivePlayer.state == THP_PLAYER_PAUSE)) {
        ActivePlayer.state = THP_PLAYER_PLAY;
        ActivePlayer.prevCount = 0;
        ActivePlayer.curCount = 0;
        ActivePlayer.retaceCount = -1;
        return TRUE;
    }
    return FALSE;
}

#pragma dont_inline on


#pragma dont_inline reset
static BOOL ProperTimingForStart()
{
    if (ActivePlayer.playFlag & THP_PLAY_SYNC_FIELD0) {
        if (VIGetNextField() == 0)
            return TRUE;
    } else if (ActivePlayer.playFlag & THP_PLAY_SYNC_FIELD1) {
        if (VIGetNextField() == 1)
            return TRUE;
    } else
        return TRUE;

    return FALSE;
}

static BOOL ProperTimingForGettingNextFrame()
{
    if ((ActivePlayer.playFlag & THP_PLAY_SYNC_FIELD0)) {
        if (VIGetNextField() == 0) {
            return TRUE;
        }
    } else if ((ActivePlayer.playFlag & THP_PLAY_SYNC_FIELD1)) {
        if (VIGetNextField() == 1) {
            return TRUE;
        }
    } else {
        s32 frameRate = ActivePlayer.header.frameRate * 100.0f;
        ActivePlayer.curCount = ActivePlayer.retaceCount * frameRate / 5994;

        if (ActivePlayer.prevCount != ActivePlayer.curCount) {
            ActivePlayer.prevCount = ActivePlayer.curCount;
            return TRUE;
        }
    }

    return FALSE;
}

#pragma dont_inline on


extern void InitAllMessageQueue(void);
extern BOOL CreateReadThread(OSPriority);
extern BOOL CreateVideoDecodeThread(OSPriority, void *);
extern BOOL CreateAudioDecodeThread(OSPriority, void *);
extern void ReadThreadStart(void);
extern void VideoDecodeThreadStart(void);
extern void AudioDecodeThreadStart(void);

#pragma dont_inline on


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


