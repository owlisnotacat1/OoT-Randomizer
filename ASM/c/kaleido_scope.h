#pragma once

#include "z64.h"

typedef signed char s8;
typedef short s16;
typedef int s32;
typedef long long s64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;

extern Audio_QueueSeqCmd(u32 cmd);

#define SEQCMD_STOP_SEQUENCE(seqPlayerIndex, fadeOutDuration)                                 \
    Audio_QueueSeqCmd((1 << 28) | 0xFF | ((u8)(seqPlayerIndex) << 24) | \
                      ((u8)(fadeOutDuration) << 16))

#define BTN_CRIGHT      0x0001
#define BTN_CLEFT       0x0002
#define BTN_CDOWN       0x0004
#define BTN_CUP         0x0008
#define BTN_R           0x0010
#define BTN_L           0x0020
#define BTN_DRIGHT      0x0100
#define BTN_DLEFT       0x0200
#define BTN_DDOWN       0x0400
#define BTN_DUP         0x0800
#define BTN_START       0x1000
#define BTN_Z           0x2000
#define BTN_B           0x4000
#define BTN_A           0x8000

#define CHECK_BTN_ALL(state, combo) (((state) & (combo)) == (combo))

typedef struct OSContPad {
    /* 0x00 */ u16 button;
    /* 0x02 */ s8 stick_x;
    /* 0x03 */ s8 stick_y;
    /* 0x04 */ u8 errno;
} OSContPad; // size = 0x06
typedef struct Input {
    /* 0x00 */ OSContPad cur;
    /* 0x06 */ OSContPad prev;
    /* 0x0C */ OSContPad press; // X/Y store delta from last frame
    /* 0x12 */ OSContPad rel; // X/Y store adjusted
} Input; // size = 0x18


typedef struct Vec3f {
    f32 x, y, z;
} Vec3f; // size = 0x0C

typedef struct Vec3s {
    s16 x, y, z;
} Vec3s; // size = 0x06

typedef enum TimerId {
    /* 0 */ TIMER_ID_MAIN, // Takes priority in both counting and drawing. See `timerState` and `timerSeconds`
    /* 1 */ TIMER_ID_SUB, // See `subTimerState` and `subTimerSeconds`
    /* 2 */ TIMER_ID_MAX
} TimerId;

typedef struct RomFile {
    /* 0x00 */ uintptr_t vromStart;
    /* 0x04 */ uintptr_t vromEnd;
} RomFile; // size = 0x8

typedef struct KaleidoMgrOverlay {
    /* 0x00 */ void* loadedRamAddr;
    /* 0x04 */ RomFile file;
    /* 0x0C */ void* vramStart;
    /* 0x10 */ void* vramEnd;
    /* 0x14 */ u32 offset; // loadedRamAddr - vramStart
    /* 0x18 */ const char* name;
} KaleidoMgrOverlay; // size = 0x1C

Vec3f gSfxDefaultPos = {0.0f, 0.0f, 0.0f};
char gSfxDefaultReverb = 0;
f32 gSfxDefaultFreqAndVolScale = 1.0f; 
#define REG_GROUPS 29 // number of REG groups, i.e. REG, SREG, OREG, etc.
#define REG_PAGES 6
#define REGS_PER_PAGE 16
#define REGS_PER_GROUP (REG_PAGES * REGS_PER_PAGE)
typedef struct RegEditor {
    /* 0x00 */ s32  regPage; // 0: no page selected (reg editor is not active); 1: first page; `REG_PAGES`: last page
    /* 0x04 */ s32  regGroup; // Indexed from 0 to `REG_GROUPS`-1. Each group has its own character to identify it.
    /* 0x08 */ s32  regCur; // Selected reg, indexed from 0 as the page start
    /* 0x0C */ s32  dPadInputPrev;
    /* 0x10 */ s32  inputRepeatTimer;
    /* 0x14 */ s16  data[REG_GROUPS * REGS_PER_GROUP]; // Accessed through *REG macros, see regs.h
} RegEditor; // size = 0x15D4

extern RegEditor* gRegEditor;

#define BASE_REG(n, r) gRegEditor->data[(n) * REGS_PER_GROUP + (r)]
#define  REG(r) BASE_REG(0, (r))
#define SREG(r) BASE_REG(1, (r))
#define OREG(r) BASE_REG(2, (r))
#define PREG(r) BASE_REG(3, (r))
#define QREG(r) BASE_REG(4, (r))
#define MREG(r) BASE_REG(5, (r))
#define YREG(r) BASE_REG(6, (r))
#define DREG(r) BASE_REG(7, (r))
#define UREG(r) BASE_REG(8, (r))
#define IREG(r) BASE_REG(9, (r))
#define ZREG(r) BASE_REG(10, (r))
#define CREG(r) BASE_REG(11, (r))
#define NREG(r) BASE_REG(12, (r))
#define KREG(r) BASE_REG(13, (r))
#define XREG(r) BASE_REG(14, (r))
#define cREG(r) BASE_REG(15, (r))
#define sREG(r) BASE_REG(16, (r))
#define iREG(r) BASE_REG(17, (r))
#define WREG(r) BASE_REG(18, (r))
#define AREG(r) BASE_REG(19, (r))
#define VREG(r) BASE_REG(20, (r))
#define HREG(r) BASE_REG(21, (r))
#define GREG(r) BASE_REG(22, (r))
#define mREG(r) BASE_REG(23, (r))
#define nREG(r) BASE_REG(24, (r))
#define BREG(r) BASE_REG(25, (r))
#define dREG(r) BASE_REG(26, (r))
#define kREG(r) BASE_REG(27, (r))
#define bREG(r) BASE_REG(28, (r))

extern void Audio_PlaySfxGeneral(u16 sfxId, Vec3f* pos, u8 token, f32* freqScale, f32* vol, s8* reverbAdd);
extern void Sram_WriteSave_call(void* sramCtx);
extern void Play_SaveSceneFlags(z64_game_t* play);
extern void Interface_SetDoAction(z64_game_t* play, u16 action);
extern void Interface_ChangeHudVisibilityMode(u16 hudVisibilityMode);
extern void func_800F64E0(u8 arg0);
//extern s16 D_8082B25C;

typedef struct ItemEquips {
    /* 0x00 */ u8 buttonItems[4];
    /* 0x04 */ u8 cButtonSlots[3];
    /* 0x08 */ u16 equipment; // a mask where each nibble corresponds to a type of equipment `EquipmentType`, and each nibble is a piece `EquipValue*`
} ItemEquips; // size = 0x0A

typedef struct Vec3i {
    s32 x, y, z;
} Vec3i; // size = 0x0C

typedef struct HorseData {
    /* 0x00 */ s16 sceneId;
    /* 0x02 */ Vec3s pos;
    /* 0x08 */ s16 angle;
} HorseData; // size = 0x0A

typedef struct SavePlayerData {
    /* 0x00  0x001C */ char newf[6]; // string "ZELDAZ"
    /* 0x06  0x0022 */ u16 deaths;
    /* 0x08  0x0024 */ char playerName[8];
    /* 0x10  0x002C */ s16 n64ddFlag;
    /* 0x12  0x002E */ s16 healthCapacity; // "max_life"
    /* 0x14  0x0030 */ s16 health; // "now_life"
    /* 0x16  0x0032 */ s8 magicLevel; // 0 for no magic/new load, 1 for magic, 2 for double magic
    /* 0x17  0x0033 */ s8 magic; // current magic available for use
    /* 0x18  0x0034 */ s16 rupees;
    /* 0x1A  0x0036 */ u16 swordHealth;
    /* 0x1C  0x0038 */ u16 naviTimer;
    /* 0x1E  0x003A */ u8 isMagicAcquired;
    /* 0x1F  0x003B */ char unk_3B[0x01];
    /* 0x20  0x003C */ u8 isDoubleMagicAcquired;
    /* 0x21  0x003D */ u8 isDoubleDefenseAcquired;
    /* 0x22  0x003E */ u8 bgsFlag;
    /* 0x23  0x003F */ u8 ocarinaGameRoundNum;
    /* 0x24  0x0040 */ ItemEquips childEquips;
    /* 0x2E  0x004A */ ItemEquips adultEquips;
    /* 0x38  0x0054 */ u32 unk_54; // this may be incorrect, currently used for alignment
    /* 0x3C  0x0058 */ char unk_58[0x0E];
    /* 0x4A  0x0066 */ s16 savedSceneId;
} SavePlayerData;

typedef struct FaroresWindData {
    /* 0x00 */ Vec3i pos;
    /* 0x0C */ s32 yaw;
    /* 0x10 */ s32 playerParams;
    /* 0x14 */ s32 entranceIndex;
    /* 0x18 */ s32 roomIndex;
    /* 0x1C */ s32 set;
    /* 0x20 */ s32 tempSwchFlags;
    /* 0x24 */ s32 tempCollectFlags;
} FaroresWindData; // size = 0x28

typedef struct Inventory {
    /* 0x00 */ u8 items[24];
    /* 0x18 */ s8 ammo[16];
    /* 0x28 */ u16 equipment; // a mask where each nibble corresponds to a type of equipment `EquipmentType`, and each bit to an owned piece `EquipInv*`
    /* 0x2C */ u32 upgrades;
    /* 0x30 */ u32 questItems;
    /* 0x34 */ u8 dungeonItems[20];
    /* 0x48 */ s8 dungeonKeys[19];
    /* 0x5B */ s8 defenseHearts;
    /* 0x5C */ s16 gsTokens;
} Inventory; // size = 0x5E

typedef struct SavedSceneFlags {
    /* 0x00 */ u32 chest;
    /* 0x04 */ u32 swch;
    /* 0x08 */ u32 clear;
    /* 0x0C */ u32 collect;
    /* 0x10 */ u32 unk;
    /* 0x14 */ u32 rooms;
    /* 0x18 */ u32 floors;
} SavedSceneFlags; // size = 0x1C

typedef struct SaveInfo {
    /* 0x0000  0x001C */ SavePlayerData playerData; // "S_Private"
    /* 0x004C  0x0068 */ ItemEquips equips;
    /* 0x0058  0x0074 */ Inventory inventory;
    /* 0x00B8  0x00D4 */ SavedSceneFlags sceneFlags[124];
    /* 0x0E48  0x0E64 */ FaroresWindData fw;
    /* 0x0E70  0x0E8C */ char unk_E8C[0x10];
    /* 0x0E80  0x0E9C */ s32 gsFlags[6];
    /* 0x0E98  0x0EB4 */ char unk_EB4[0x4];
    /* 0x0E9C  0x0EB8 */ s32 highScores[7];
    /* 0x0EB8  0x0ED4 */ u16 eventChkInf[14]; // "event_chk_inf"
    /* 0x0ED4  0x0EF0 */ u16 itemGetInf[4]; // "item_get_inf"
    /* 0x0EDC  0x0EF8 */ u16 infTable[30]; // "inf_table"
    /* 0x0F18  0x0F34 */ char unk_F34[0x04];
    /* 0x0F1C  0x0F38 */ u32 worldMapAreaData; // "area_arrival"
    /* 0x0F20  0x0F3C */ char unk_F3C[0x4];
    /* 0x0F24  0x0F40 */ u8 scarecrowLongSongSet;
    /* 0x0F25  0x0F41 */ u8 scarecrowLongSong[0x360];
    /* 0x1285  0x12A1 */ char unk_12A1[0x24];
    /* 0x12A9  0x12C5 */ u8 scarecrowSpawnSongSet;
    /* 0x12AA  0x12C6 */ u8 scarecrowSpawnSong[0x80];
    /* 0x132A  0x1346 */ char unk_1346[0x02];
    /* 0x132C  0x1348 */ HorseData horseData;
    /* 0x1336  0x1352 */ u16 checksum; // "check_sum"
} SaveInfo;

typedef struct Save {
    /* 0x00 */ s32 entranceIndex;
    /* 0x04 */ s32 linkAge; // 0: Adult; 1: Child (see enum `LinkAge`)
    /* 0x08 */ s32 cutsceneIndex;
    /* 0x0C */ u16 dayTime; // "zelda_time"
    /* 0x10 */ s32 nightFlag;
    /* 0x14 */ s32 totalDays;
    /* 0x18 */ s32 bgsDayCount; // increments with totalDays, can be cleared with `Environment_ClearBgsDayCount`
    /* 0x1C */ SaveInfo info; // "information"
} Save;

typedef struct SaveContext {
    /* 0x0000 */ Save save; // "memory"
    /* 0x1354 */ s32 fileNum; // "file_no"
    /* 0x1358 */ char unk_1358[0x0004];
    /* 0x135C */ s32 gameMode;
    /* 0x1360 */ s32 sceneLayer; // "counter"
    /* 0x1364 */ s32 respawnFlag; // "restart_flag"
    /* 0x1368 */ RespawnData respawn[RESPAWN_MODE_MAX]; // "restart_data"
    /* 0x13BC */ f32 entranceSpeed;
    /* 0x13C0 */ u16 entranceSound;
    /* 0x13C2 */ char unk_13C2[0x0001];
    /* 0x13C3 */ u8 retainWeatherMode;
    /* 0x13C4 */ s16 dogParams;
    /* 0x13C6 */ u8 envHazardTextTriggerFlags;
    /* 0x13C7 */ u8 showTitleCard;
    /* 0x13C8 */ s16 nayrusLoveTimer;
    /* 0x13CA */ char unk_13CA[0x0002];
    /* 0x13CC */ s16 rupeeAccumulator;
    /* 0x13CE */ s16 timerState; // See `TimerState`
    /* 0x13D0 */ s16 timerSeconds;
    /* 0x13D2 */ s16 subTimerState; // See `SubTimerState`
    /* 0x13D4 */ s16 subTimerSeconds;
    /* 0x13D6 */ s16 timerX[TIMER_ID_MAX];
    /* 0x13DA */ s16 timerY[TIMER_ID_MAX];
    /* 0x13DE */ char unk_13DE[0x0002];
    /* 0x13E0 */ u8 seqId;
    /* 0x13E1 */ u8 natureAmbienceId;
    /* 0x13E2 */ u8 buttonStatus[5];
    /* 0x13E7 */ u8 forceRisingButtonAlphas; // if btn alphas are updated through Interface_DimButtonAlphas, instead update them through Interface_RaiseButtonAlphas
    /* 0x13E8 */ u16 nextHudVisibilityMode; // triggers the hud to change visibility mode to the requested value. Reset to HUD_VISIBILITY_NO_CHANGE when target is reached
    /* 0x13EA */ u16 hudVisibilityMode; // current hud visibility mode
    /* 0x13EC */ u16 hudVisibilityModeTimer; // number of frames in the transition to a new hud visibility mode. Used to step alpha
    /* 0x13EE */ u16 prevHudVisibilityMode; // used to store and recover hud visibility mode for pause menu and text boxes
    /* 0x13F0 */ s16 magicState; // determines magic meter behavior on each frame
    /* 0x13F2 */ s16 prevMagicState; // used to resume the previous state after adding or filling magic
    /* 0x13F4 */ s16 magicCapacity; // maximum magic available
    /* 0x13F6 */ s16 magicFillTarget; // target used to fill magic. Target can either be full capacity (Magic_Fill, magic upgrades), or the saved magic amount (loading a file, game over)
    /* 0x13F8 */ s16 magicTarget; // target for magic to step to when adding or consuming magic
    /* 0x13FA */ u16 eventInf[4]; // "event_inf"
    /* 0x1402 */ u16 mapIndex; // intended for maps/minimaps but commonly used as the dungeon index
    /* 0x1404 */ u16 minigameState;
    /* 0x1406 */ u16 minigameScore; // "yabusame_total"
    /* 0x1408 */ char unk_1408[0x0001];
    /* 0x1409 */ u8 language; // NTSC 0: Japanese; 1: English | PAL 0: English; 1: German; 2: French
    /* 0x140A */ u8 audioSetting;
    /* 0x140B */ char unk_140B[0x0001];
    /* 0x140C */ u8 zTargetSetting; // 0: Switch; 1: Hold
    /* 0x140E */ u16 forcedSeqId; // immediately start playing the sequence if set
    /* 0x1410 */ u8 cutsceneTransitionControl; // context dependent usage: can either trigger a delayed fade or control fill alpha
    /* 0x1411 */ char unk_1411[0x0001];
    /* 0x1412 */ u16 nextCutsceneIndex;
    /* 0x1414 */ u8 cutsceneTrigger;
    /* 0x1415 */ u8 chamberCutsceneNum;
    /* 0x1416 */ u16 nextDayTime; // "next_zelda_time"
    /* 0x1418 */ u8 transFadeDuration;
    /* 0x1419 */ u8 transWipeSpeed;
    /* 0x141A */ u16 skyboxTime;
    /* 0x141C */ u8 dogIsLost;
    /* 0x141D */ u8 nextTransitionType;
    /* 0x141E */ char unk_141E[0x0002];
    /* 0x1420 */ s16 worldMapArea;
    /* 0x1422 */ s16 sunsSongState; // controls the effects of suns song
    /* 0x1424 */ s16 healthAccumulator;
} SaveContext; // size = 0x1428


typedef enum DoAction {
    /* 0x00 */ DO_ACTION_ATTACK,
    /* 0x01 */ DO_ACTION_CHECK,
    /* 0x02 */ DO_ACTION_ENTER,
    /* 0x03 */ DO_ACTION_RETURN,
    /* 0x04 */ DO_ACTION_OPEN,
    /* 0x05 */ DO_ACTION_JUMP,
    /* 0x06 */ DO_ACTION_DECIDE,
    /* 0x07 */ DO_ACTION_DIVE,
    /* 0x08 */ DO_ACTION_FASTER,
    /* 0x09 */ DO_ACTION_THROW,
    /* 0x0A */ DO_ACTION_NONE, // in do_action_static, the texture at this position is NAVI, however this value is in practice the "No Action" value
    /* 0x0B */ DO_ACTION_CLIMB,
    /* 0x0C */ DO_ACTION_DROP,
    /* 0x0D */ DO_ACTION_DOWN,
    /* 0x0E */ DO_ACTION_SAVE,
    /* 0x0F */ DO_ACTION_SPEAK,
    /* 0x10 */ DO_ACTION_NEXT,
    /* 0x11 */ DO_ACTION_GRAB,
    /* 0x12 */ DO_ACTION_STOP,
    /* 0x13 */ DO_ACTION_PUTAWAY,
    /* 0x14 */ DO_ACTION_REEL,
    /* 0x15 */ DO_ACTION_1,
    /* 0x16 */ DO_ACTION_2,
    /* 0x17 */ DO_ACTION_3,
    /* 0x18 */ DO_ACTION_4,
    /* 0x19 */ DO_ACTION_5,
    /* 0x1A */ DO_ACTION_6,
    /* 0x1B */ DO_ACTION_7,
    /* 0x1C */ DO_ACTION_8,
    /* 0x1D */ DO_ACTION_MAX
} DoAction;

typedef enum HudVisibilityMode {
    /*  0 */ HUD_VISIBILITY_NO_CHANGE,
    /*  1 */ HUD_VISIBILITY_NOTHING,
    /*  2 */ HUD_VISIBILITY_NOTHING_ALT, // Identical to HUD_VISIBILITY_NOTHING
    /*  3 */ HUD_VISIBILITY_HEARTS_FORCE, // See above
    /*  4 */ HUD_VISIBILITY_A,
    /*  5 */ HUD_VISIBILITY_A_HEARTS_MAGIC_FORCE, // See above
    /*  6 */ HUD_VISIBILITY_A_HEARTS_MAGIC_MINIMAP_FORCE, // See above
    /*  7 */ HUD_VISIBILITY_ALL_NO_MINIMAP_BY_BTN_STATUS, // Only raises button alphas if not disabled
    /*  8 */ HUD_VISIBILITY_B,
    /*  9 */ HUD_VISIBILITY_HEARTS_MAGIC,
    /* 10 */ HUD_VISIBILITY_B_ALT, // Identical to HUD_VISIBILITY_B
    /* 11 */ HUD_VISIBILITY_HEARTS,
    /* 12 */ HUD_VISIBILITY_A_B_MINIMAP,
    /* 13 */ HUD_VISIBILITY_HEARTS_MAGIC_FORCE, // See above
    /* 50 */ HUD_VISIBILITY_ALL = 50, // Only raises button alphas if not disabled
    /* 52 */ HUD_VISIBILITY_NOTHING_INSTANT = 52
} HudVisibilityMode;