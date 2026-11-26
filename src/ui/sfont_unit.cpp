extern "C" {
#pragma readonly_strings on
#pragma dont_inline on
#pragma bool off
#include "types.h"

typedef struct SJObj {
    u8 pad_00[8];
    struct SJObj *next;
    u32 pad_0C;
    struct SJObj *child;
    u8 pad_14[0x38 - 0x14];
    f32 tx;
} SJObj;
extern int sprintf(char *s, const char *fmt, ...);
extern void *LoadArc2(char *name);
extern void sMakeMatrix(SJObj *joint);
extern void __assert(const char *file, s32 line, const char *expr);

void ascPrologue(void);
#pragma force_active on
static void *ascFile[5];
static f32 ascH[5][400];
static s32 sString[8000];
static s32 FontData;
static s32 LastSheet;
static s16 FontSize;
static s16 FontSpace;
static s32 camFont;
static s32 sStringNow;
s32 Sky __attribute__((aligned(8))) ;
#pragma force_active off
static const u32 lit_371[79] = {
    0x824F8250, 0x82518252, 0x82538254, 0x82558256, 0x82578258, 0x82608261, 0x82628263, 0x82648265,
    0x82668267, 0x82688269, 0x826A826B, 0x826C826D, 0x826E826F, 0x82708271, 0x82728273, 0x82748275,
    0x82768277, 0x82788279, 0x815E817C, 0x8169816A, 0x81958149, 0x8148828D, 0x83BF83C0, 0x8140817B,
    0x81978197, 0x83418343, 0x83458347, 0x83498394, 0x834A834C, 0x834E8350, 0x8352834B, 0x834D834F,
    0x83518353, 0x83548356, 0x8358835A, 0x835C8355, 0x83578359, 0x835B835D, 0x835E8360, 0x83638365,
    0x8367835F, 0x83618364, 0x83668368, 0x8369836A, 0x836B836C, 0x836D836E, 0x83718374, 0x8377837A,
    0x836F8372, 0x83758378, 0x837B837D, 0x837E8380, 0x83818382, 0x83708373, 0x83768379, 0x837C8384,
    0x83868388, 0x8389838A, 0x838B838C, 0x838D838F, 0x83928393, 0x815B8340, 0x83428344, 0x83468348,
    0x83628383, 0x83858387, 0x88EA94CA, 0x95BA8BA4, 0x98618D91, 0x92E98D91, 0x88EB93F3, 0x8EAE8B8C,
    0x8C5E8CC0, 0x92E897CA, 0x8E598145, 0x8755828B, 0x91E5906C, 0x8E718B9F, 0x00000000
};
static const char lit_372[133] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ/-()&!?m@* +@@\xb1\xb2\xb3\xb4\xb5@\xb6\xb7\xb8\xb9\xba@@@@@\xbb\xbc\xbd\xbe\xbf@@@@@\xc0\xc1\xc2\xc3\xc4@@@@@\xc5\xc6\xc7\xc8\xc9\xca\xcb\xcc\xcd\xce@@@@@\xcf\xd0\xd1\xd2\xd3@@@@@\xd4\xd5\xd6\xd7\xd8\xd9\xda\xdb\xdc\xa6\xdd\xb0\xa7\xa8\xa9\xaa\xab\xaf\xac\xad\xae";
static s8 *asc00 = (s8 *)lit_371;
extern s32 getAscNum1(s8 character);

s32 getAscNum(char *text)
{
    s8 first = text[0], second = text[1];
    u8 lead = first & 0xE0;
    s8 *characters;
    s32 index;

    if (lead != 0xE0 && lead != 0x80)
        return getAscNum1(first);
    characters = asc00;
    if (first == 0)
        return -1;
    if (second == 0)
        return -1;
    index = 0;
    while (*characters) {
        if (first == characters[0] && second == characters[1])
            return index;
        characters += 2;
        index++;
    }
    return -1;
}

void ascPrologue(void)
{
    char name[0x100];
    s32 i;
    s32 j;
    SJObj *jobj;

    for (i = 0; i < 5; i++) {
        sprintf(name, "ascii/ascii%02d.dat", i);
        ascFile[i] = LoadArc2(name);
        if (ascFile[i] != 0) {
            jobj = *(SJObj **)((u8 *)ascFile[i] + 0x3c);
            for (j = 0; j < 400; j++) {
                ascH[i][j] = 0.0f;
            }
            if (jobj != (SJObj *)0) {
                sMakeMatrix(jobj);
                jobj = jobj ? jobj->child : 0;
                for (j = 0; jobj != 0; j++) {
                    jobj ? (void)0 : __assert("jobj.h", 1009, "jobj");
                    ascH[i][j] = -jobj->tx;
                    jobj = jobj ? jobj->next : 0;
                }
            }
        }
    }
}

static const u32 lit_681[3] = { 0x00000000, 0x00000000, 0x00000000 };
static const u32 lit_682[3] = { 0x00000000, 0x00000000, 0xC5BB8000 };
static const char lit_811[21] = "Licensed by Nintendo";
static const char lit_845[22] = "G A M E   C L E A R .";
static const char lit_847[28] = "Thank you for your playing!";
}
