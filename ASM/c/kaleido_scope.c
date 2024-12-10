#include "z64.h"
#include "kaleido_scope.h"
#include "stdint.h"


extern SaveContext gSaveContext;

void kaleidoScope_Case7(z64_game_t* play) {
    z64_pause_ctxt_t* pauseCtx = &play->pause_ctxt;
    Audio_PlaySfxGeneral(18440, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            switch (pauseCtx->unk_1EC) {
                case 0:
                    pauseCtx->unk_204 -= 314.0f / WREG(6);
                    WREG(16) -= WREG(25) / WREG(6);
                    WREG(17) -= WREG(26) / WREG(6);
                    if (pauseCtx->unk_204 <= -628.0f) {
                        pauseCtx->unk_204 = -628.0f;
                        pauseCtx->unk_1EC = 1;
                    }
                    break;

                case 1:
                Audio_PlaySfxGeneral(18440, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                    if (play->common.input[0].pad_pressed.a) {
        //config variable check here
                        if (1 == 1) {
                            if (pauseCtx->prompt_choice != 0) {
                                pauseCtx->prompt_choice = 0;
                                Audio_PlaySfxGeneral(18440, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
                                pauseCtx->state = PAUSE_STATE_RETURN_TO_TITLE_PROMPT;
                            } else {
                                Audio_PlaySfxGeneral(18467, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);               
                                pauseCtx->prompt_choice = 0;
                                //Play_SaveSceneFlags(play);
                                //gSaveContext.save.info.playerData.savedSceneId = play->scene_index;
                                //Sram_WriteSave_call(&play->unk_0F_[0x0207]);
                                pauseCtx->state = PAUSE_STATE_RETURN_TO_TITLE_PROMPT_TIMER;
                                D_8082B25C = 90;
                            }
                        } else {
                            if (pauseCtx->prompt_choice != 0) {
                            
                                Interface_SetDoAction(play, DO_ACTION_NONE);
                                gSaveContext.buttonStatus[0] = gSaveContext.buttonStatus[1] = gSaveContext.buttonStatus[2] =
                                    gSaveContext.buttonStatus[3] = 0;
                                gSaveContext.hudVisibilityMode = HUD_VISIBILITY_NO_CHANGE;
                                Interface_ChangeHudVisibilityMode(HUD_VISIBILITY_ALL);
                                pauseCtx->unk_1EC = 2;
                                WREG(2) = -6240;
                                YREG(8) = pauseCtx->unk_204;
                                func_800F64E0(0);
                            } else {
                                Audio_PlaySfxGeneral(18467, &gSfxDefaultPos, 4,
                                                     &gSfxDefaultFreqAndVolScale, &gSfxDefaultFreqAndVolScale,
                                                     &gSfxDefaultReverb);
                                Play_SaveSceneFlags(play);

                                gSaveContext.save.info.playerData.savedSceneId = play->scene_index;
                                Sram_WriteSave_call(&play->unk_0F_[0x0207]);
                                pauseCtx->unk_1EC = 4;
                                D_8082B25C = 3;
                            }
                        }
                    } else if (play->common.input[0].pad_pressed.s ||
                                play->common.input[0].pad_pressed.b) {
                        Interface_SetDoAction(play, DO_ACTION_NONE);
                        pauseCtx->unk_1EC = 2;
                        WREG(2) = -6240;
                        YREG(8) = pauseCtx->unk_204;
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
                            pauseCtx->unk_1EC = 5;
                            WREG(2) = -6240;
                            YREG(8) = pauseCtx->unk_204;
                            func_800F64E0(0);
                        }
                        break;
//
                case 3:
                case 6:
                    pauseCtx->unk_204 += 314.0f / WREG(6);
                    WREG(16) += WREG(25) / WREG(6);
                    WREG(17) += WREG(26) / WREG(6);
                    if (pauseCtx->unk_204 >= -314.0f) {
                        pauseCtx->state = PAUSE_STATE_MAIN;
                        pauseCtx->unk_1EC = 0;
                        pauseCtx->unk_1F4 = pauseCtx->unk_1F8 = pauseCtx->unk_1FC = pauseCtx->unk_200 = 0.0f;
                        pauseCtx->unk_204 = -314.0f;
                    }
                    break;

                case 2:
                case 5:
                    if (pauseCtx->unk_204 != (YREG(8) + 160.0f)) {
                        pauseCtx->unk_1F4 = pauseCtx->unk_1F8 = pauseCtx->unk_1FC = pauseCtx->unk_200 +=
                            160.0f / WREG(6);
                        pauseCtx->unk_204 += 160.0f / WREG(6);
                        pauseCtx->info_panel_offset_y -= 40 / WREG(6);
                        WREG(16) -= WREG(25) / WREG(6);
                        WREG(17) -= WREG(26) / WREG(6);
                        XREG(5) -= 150 / WREG(6);
                        pauseCtx->alpha -= (u16)(255 / WREG(6));
                        if (pauseCtx->unk_204 == (YREG(8) + 160.0f)) {
                            pauseCtx->alpha = 0;
                        }
                    } else {
                        pauseCtx->debugState = 0;
                        pauseCtx->state = PAUSE_STATE_RESUME_GAMEPLAY;
                        pauseCtx->unk_1F4 = pauseCtx->unk_1F8 = pauseCtx->unk_1FC = pauseCtx->unk_200 = 160.0f;
                        pauseCtx->item_id = 999;
                        pauseCtx->changing = PAUSE_MAIN_STATE_IDLE;
                        pauseCtx->unk_204 = -434.0f;
                    }
                    break;

                default:
                    break;
            }

}

void kaleidoScope_Case20(z64_game_t* play) {
    z64_pause_ctxt_t* pauseCtx = &play->pause_ctxt;
    Input* input = &play->common.input[0];

    if (play->common.input[0].pad_pressed.a || play->common.input[0].pad_pressed.s) {
        if (pauseCtx->prompt_choice == 0) {
            Audio_PlaySfxGeneral(18467, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            Interface_SetDoAction(play, DO_ACTION_NONE);
            pauseCtx->unk_204 = 2;
            WREG(2) = -6240;
            YREG(8) = pauseCtx->unk_204;
            func_800F64E0(0);
            gSaveContext.buttonStatus[0] = gSaveContext.buttonStatus[1] = gSaveContext.buttonStatus[2] =
                gSaveContext.buttonStatus[3] = 0;
            gSaveContext.hudVisibilityMode = HUD_VISIBILITY_NO_CHANGE;
            Interface_ChangeHudVisibilityMode(HUD_VISIBILITY_ALL);
            pauseCtx->state = PAUSE_STATE_SAVE_PROMPT;
            return;
        } else {
            Audio_PlaySfxGeneral(NA_SE_SY_DECIDE, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            // returns to title
            SEQCMD_STOP_SEQUENCE(0, 10);
            SEQCMD_STOP_SEQUENCE(3, 10);
            pauseCtx->state = PAUSE_STATE_REUTRN_TO_TITLE;
        }
    }
}

void kaleidoScope_Case21(z64_game_t* play) {
    z64_pause_ctxt_t* pauseCtx = &play->pause_ctxt;
    Input* input = &play->common.input[0];

    D_8082B25C--;
    if (D_8082B25C == 0) {
        pauseCtx->state = PAUSE_STATE_RETURN_TO_TITLE_PROMPT;
    } else if ((D_8082B25C <= 80) &&
               (play->common.input[0].pad_pressed.a || play->common.input[0].pad_pressed.s)) {
        pauseCtx->state = PAUSE_STATE_RETURN_TO_TITLE_PROMPT;
        func_800F64E0(0);
    }
}

static s16 D_8082A6E0[] = { 100, 255 };

void KaleidoScope_UpdatePrompt(z64_game_t* play) {
    PauseContext* pauseCtx = &play->pause_ctxt;
    Input* input = &z64_game.common.input[0];
    s8 stickAdjX = input->rel.stick_x;
    s16 step;

    if (((pauseCtx->state == PAUSE_STATE_SAVE_PROMPT) && (pauseCtx->unk_1EC == 1)) ||
        (pauseCtx->state == PAUSE_STATE_14) || (pauseCtx->state == PAUSE_STATE_16)) {
        if ((pauseCtx->promptChoice == 0) && (stickAdjX >= 30)) {
            Audio_PlaySfxGeneral(NA_SE_SY_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            pauseCtx->promptChoice = 4;
        } else if ((pauseCtx->promptChoice != 0) && (stickAdjX <= -30)) {
            Audio_PlaySfxGeneral(NA_SE_SY_CURSOR, &gSfxDefaultPos, 4, &gSfxDefaultFreqAndVolScale,
                                 &gSfxDefaultFreqAndVolScale, &gSfxDefaultReverb);
            pauseCtx->promptChoice = 0;
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