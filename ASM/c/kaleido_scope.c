#include "z64.h"
#include "kaleido_scope.h"
#include "stdint.h"


extern SaveContext gSaveContext;

static s32 saveAndQuitConfig = 0;

void kaleidoScope_Case7(z64_game_t* play) {
    z64_pause_ctxt_t* pauseCtx = &play->pause_ctxt;
            switch (play->pause_ctxt.unk_1EC) {
                case 0:
                    play->pause_ctxt.unk_204 -= 314.0f / WREG(6);
                    WREG(16) -= WREG(25) / WREG(6);
                    WREG(17) -= WREG(26) / WREG(6);
                    if (play->pause_ctxt.unk_204 <= -628.0f) {
                        play->pause_ctxt.unk_204 = -628.0f;
                        play->pause_ctxt.unk_1EC = 1;
                    }
                    break;

                case 1:
                    if (play->common.input[0].pad_pressed.a) {
                        //config variable check here
                        if (saveAndQuitConfig == 1) {

                            if (play->pause_ctxt.prompt_choice != 0) {
                            
                                Interface_SetDoAction(play, DO_ACTION_NONE);
                                gSaveContext.buttonStatus[0] = gSaveContext.buttonStatus[1] = gSaveContext.buttonStatus[2] =
                                    gSaveContext.buttonStatus[3] = 0;
                                gSaveContext.hudVisibilityMode = HUD_VISIBILITY_NO_CHANGE;
                                Interface_ChangeHudVisibilityMode(HUD_VISIBILITY_ALL);
                                play->pause_ctxt.unk_1EC = 2;
                                WREG(2) = -6240;
                                YREG(8) = play->pause_ctxt.unk_204;
                                func_800F64E0(0);
                            } else {
                                Audio_PlaySfxGeneral(18467, &gSfxDefaultPos, 4,
                                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale,
                                                     &gSfxDefaultReverb);
                                Play_SaveSceneFlags(play);

                                gSaveContext.save.info.playerData.savedSceneId = play->scene_index;
                                Sram_WriteSave_call(&play->unk_0F_[0x0207]);
                                play->pause_ctxt.unk_1EC = 4;
                                D_8082B25C = 3;
                            }
                        } else {
                            if (play->pause_ctxt.prompt_choice != 0) {
                            // no
                            play->pause_ctxt.prompt_choice = 0;
                            Audio_PlaySfxGeneral(NA_SE_SY_DECIDE, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                            play->pause_ctxt.state = PAUSE_STATE_RETURN_TO_TITLE_PROMPT;
                            //gameOverCtx->state++;
                        } else {
                            // yes 
                            Audio_PlaySfxGeneral(18467, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                            play->pause_ctxt.prompt_choice = 0;
                            Play_SaveSceneFlags(play);
                            gSaveContext.save.info.playerData.savedSceneId = play->scene_index;
                            Sram_WriteSave_call(&play->unk_0F_[0x0207]);
                            play->pause_ctxt.state = PAUSE_STATE_RETURN_TO_TITLE_PROMPT_TIMER;
                            D_8082B25C = 3;
                        }
                        }
                        
                    } else if (play->common.input[0].pad_pressed.s ||
                                play->common.input[0].pad_pressed.b) {
                        Interface_SetDoAction(play, DO_ACTION_NONE);
                        play->pause_ctxt.unk_1EC = 2;
                        WREG(2) = -6240;
                        YREG(8) = play->pause_ctxt.unk_204;
                        func_800F64E0(0);
                        gSaveContext.buttonStatus[0] = gSaveContext.buttonStatus[1] = gSaveContext.buttonStatus[2] =
                            gSaveContext.buttonStatus[3] = 0;
                        gSaveContext.hudVisibilityMode = HUD_VISIBILITY_NO_CHANGE;
                        Interface_ChangeHudVisibilityMode(HUD_VISIBILITY_ALL);
                    }
                    break;

                    case 4:
                        if (play->common.input[0].pad_pressed.b || play->common.input[0].pad_pressed.a ||
                            play->common.input[0].pad_pressed.s || (--D_8082B25C == 0)) {
                            Interface_SetDoAction(play, DO_ACTION_NONE);
                            gSaveContext.buttonStatus[0] = gSaveContext.buttonStatus[1] = gSaveContext.buttonStatus[2] =
                            gSaveContext.buttonStatus[3] = 0;
                            gSaveContext.hudVisibilityMode = HUD_VISIBILITY_NO_CHANGE;
                            Interface_ChangeHudVisibilityMode(HUD_VISIBILITY_ALL);
                            play->pause_ctxt.unk_1EC = 5;
                            WREG(2) = -6240;
                            YREG(8) = play->pause_ctxt.unk_204;
                            func_800F64E0(0);
                        }
                        break;
//
                case 3:
                case 6:
                    play->pause_ctxt.unk_204 += 314.0f / WREG(6);
                    WREG(16) += WREG(25) / WREG(6);
                    WREG(17) += WREG(26) / WREG(6);
                    if (play->pause_ctxt.unk_204 >= -314.0f) {
                        play->pause_ctxt.state = PAUSE_STATE_MAIN;
                        play->pause_ctxt.unk_1EC = 0;
                        play->pause_ctxt.unk_1F4 = play->pause_ctxt.unk_1F8 = play->pause_ctxt.unk_1FC = play->pause_ctxt.unk_200 = 0.0f;
                        play->pause_ctxt.unk_204 = -314.0f;
                    }
                    break;

                case 2:
                case 5:
                    if (play->pause_ctxt.unk_204 != (YREG(8) + 160.0f)) {
                        play->pause_ctxt.unk_1F4 = play->pause_ctxt.unk_1F8 = play->pause_ctxt.unk_1FC = play->pause_ctxt.unk_200 +=
                            160.0f / WREG(6);
                        play->pause_ctxt.unk_204 += 160.0f / WREG(6);
                        play->pause_ctxt.info_panel_offset_y -= 40 / WREG(6);
                        WREG(16) -= WREG(25) / WREG(6);
                        WREG(17) -= WREG(26) / WREG(6);
                        XREG(5) -= 150 / WREG(6);
                        play->pause_ctxt.alpha -= (u16)(255 / WREG(6));
                        if (play->pause_ctxt.unk_204 == (YREG(8) + 160.0f)) {
                            play->pause_ctxt.alpha = 0;
                        }
                    } else {
                        play->pause_ctxt.debugState = 0;
                        play->pause_ctxt.state = PAUSE_STATE_RESUME_GAMEPLAY;
                        play->pause_ctxt.unk_1F4 = play->pause_ctxt.unk_1F8 = play->pause_ctxt.unk_1FC = play->pause_ctxt.unk_200 = 160.0f;
                        play->pause_ctxt.item_id = 999;
                        play->pause_ctxt.changing = PAUSE_MAIN_STATE_IDLE;
                        play->pause_ctxt.unk_204 = -434.0f;
                    }
                    break;

                default:
                    break;
            }

}

void kaleidoScope_Case21(z64_game_t* play) {
    z64_pause_ctxt_t* pauseCtx = &play->pause_ctxt;
    Input* input = &play->common.input[0];

    if (play->common.input[0].pad_pressed.a || play->common.input[0].pad_pressed.s) {
        if (play->pause_ctxt.prompt_choice == 0) {
            Audio_PlaySfxGeneral(18467, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            Interface_SetDoAction(play, DO_ACTION_NONE);
            play->pause_ctxt.unk_204 = 2;
            WREG(2) = -6240;
            YREG(8) = play->pause_ctxt.unk_204;
            func_800F64E0(0);
            gSaveContext.buttonStatus[0] = gSaveContext.buttonStatus[1] = gSaveContext.buttonStatus[2] =
                gSaveContext.buttonStatus[3] = 0;
            gSaveContext.hudVisibilityMode = HUD_VISIBILITY_NO_CHANGE;
            Interface_ChangeHudVisibilityMode(HUD_VISIBILITY_ALL);
            play->pause_ctxt.state = PAUSE_STATE_SAVE_PROMPT;
            return;
        } else {
            Audio_PlaySfxGeneral(NA_SE_SY_DECIDE, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            // returns to title
            SEQCMD_STOP_SEQUENCE(0, 10);
            SEQCMD_STOP_SEQUENCE(3, 10);
            play->pause_ctxt.state = PAUSE_STATE_REUTRN_TO_TITLE;
        }
    }
}

void kaleidoScope_Case20(z64_game_t* play) {
    z64_pause_ctxt_t* pauseCtx = &play->pause_ctxt;

    D_8082B25C--;
    if (D_8082B25C == 0) {
        play->pause_ctxt.state = PAUSE_STATE_RETURN_TO_TITLE_PROMPT;
    } else if ((D_8082B25C <= 80) &&
               (play->common.input[0].pad_pressed.a || play->common.input[0].pad_pressed.s)) {
        play->pause_ctxt.state = PAUSE_STATE_RETURN_TO_TITLE_PROMPT;
        func_800F64E0(0);
    }
}

static s16 D_8082A6E0[] = { 100, 255 };

void KaleidoScope_UpdatePrompt(z64_game_t* play) {
    PauseContext* pauseCtx = &play->pause_ctxt;
    s8 stickAdjX = play->common.input[0].adjusted_x;
    s16 step;

    if (((play->pause_ctxt.state == PAUSE_STATE_SAVE_PROMPT) && (play->pause_ctxt.unk_1EC == 1)) ||
        (play->pause_ctxt.state == PAUSE_STATE_14) || (play->pause_ctxt.state == PAUSE_STATE_16) || (pauseCtx->state == PAUSE_STATE_RETURN_TO_TITLE_PROMPT)) {
        if ((play->pause_ctxt.prompt_choice == 0) && (stickAdjX >= 30)) {
            Audio_PlaySfxGeneral(NA_SE_SY_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            play->pause_ctxt.prompt_choice = 4;
        } else if ((play->pause_ctxt.prompt_choice != 0) && (stickAdjX <= -30)) {
            Audio_PlaySfxGeneral(NA_SE_SY_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            play->pause_ctxt.prompt_choice = 0;
        }

        step = ABS(VREG(61) - D_8082A6E0[VREG(62)]) / VREG(63);
        if (VREG(61) >= D_8082A6E0[VREG(62)]) {
            VREG(61) -= step;
        } else {
            VREG(61) += step;
        }

        VREG(63)--;
        if (VREG(63) == 0) {
            VREG(61) = D_8082A6E0[VREG(62)];
            VREG(63) = VREG(60) + VREG(62);
            VREG(62) ^= 1;
        }
    }
}