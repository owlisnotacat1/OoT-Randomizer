; Pause screen

.headersize(0x808137C0 - 0x00BB11E0)

.org 0x8082389C
    b       kaleidoScope_yOffsetConditionHack
    nop
    nop
    nop
    nop

.org 0x808264dc
    b       kaleidoScope_SwitchCaseHack ; this branch is to a modified version of the pauseCtx->state switch case
    ori     at, at, 0x760           ; replaced code 
    nop
    nop
    nop
    nop
@@return:
    nop

.org 0x80820d94
    b       KaleidoScope_DrawPages_ConditionHack
    nop
    nop
    nop
    nop
    nop
    nop
KaleidoScope_DrawPages_ConditionHack_return:

.org 0x8082FBFC
    .word 0x45013ED4 ; should relocate hi(0x8082A388)
    .word 0x46013ED8 ; should relocate lo(0x8082A388)
.org 0x8082F780
    .word 0x45013FA8 ; should relocate hi(0x80829E40)
    .word 0x46013FB8 ; should relocate lo(0x80829E40)

.org 0x8081E978
    jal     KaleidoScope_UpdatePrompt
    nop
    lw      ra, 0x001C(sp)
    jr      ra
    addiu   sp, sp, 0x0038

.org 0x80827568
    or      a0, s1, zero            ; loads playstate pointer into a0 before calling case 7 function
    jal     kaleidoScope_Case7      ; replcacement logic for the entirety of case 7
    nop
    b       0x80828BE4              ; jumps to return section of kaleidoScope_Update
    nop

.org 0x8082133C
    b       KaleidoScope_Draw_ContinuePromtHack
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
KaleidoScope_Draw_ContinuePromtHack_return:

.org 0x80827690
kaleidoScope_SwitchCaseHack:
    addu    s0, s1, at 
    lui     at, 0x8082
    addiu   at, 0xA388
    lui     t8, hi(D_8082B25C_RELOCATED)
    addiu   t8, t8, lo(D_8082B25C_RELOCATED)
    sw      at, 0(t8) 
    lhu     t8, 0x01D4(s0)          ; loads pauseCtx->state into t8
    ori     at, zero, 20
    beq     t8, at, @@case20        ; jumps to case 20 function (not working yet but thats not the issue)
    addiu   at, at, 1               ; increment at to 21
    beq     t8, at, @@case21        ; jumps to case 21 function (not working yet but thats not the issue)
    addiu   at, at, 1               ; increment at to 22
    beq     t8, at, @@case22        ; jumps to case 22 (identical to case 17 but pauseCtx->state is referenced by other code and it being 17 causes the game over text to be drawn)
    addiu   t9, t8, 0xFFFD          ; replaced code from above
    sltiu   at, t9, 0x0011          ; replaced code from above
    beq     at, zero, 0x80828BE4    ; replaced code from above
    sll     t9, t9, 0x0002          ; replaced code from above
    b       0x808264f4              ; returns back to @@return to continue if none of the new or modified cases are being called and returns to the original code
    nop
@@case20:
    jal     kaleidoScope_Case20
    or      a0, s1, zero
    b       0x80828BE4              ; jumps to return section of kaleidoScope_Update
    nop
@@case21:
    jal     kaleidoScope_Case21
    or      a0, s1, zero
    b       0x80828BE4              ; jumps to return section of kaleidoScope_Update
    nop
@@case22:
    b       0x808287D8              ; jumps to case 17
    nop
    
;0x8039CAA4
KaleidoScope_DrawPages_ConditionHack:
    addiu   at, zero, 7
    beq     a0, at, 0x80820db0
    addiu   at, zero, 21
    beq     a0, at, 0x80820db0
    addiu   at, zero, 20
    beq     a0, at, 0x80820db0
    slti    at, a0, 0x0008
    bne     at, zero, 0x80821580
    slti    at, a0, 0x0012
    beql    at, zero, 0x80821584
    lw      ra, 0x0024(sp)
    b       KaleidoScope_DrawPages_ConditionHack_return
    nop
KaleidoScope_Draw_ContinuePromtHack:
    addiu   at, zero, 0x10
    or      s6, zero, a0
    beq     a0, at, KaleidoScope_Draw_Texture_Logic
    li      at, 0x14
    beq     a0, at, KaleidoScope_Draw_Texture_Logic
    li      at, 0x15
    beq     a0, at, KaleidoScope_Draw_Texture_Logic
    li      at, 0x11
    bnel    a0, at, 0x808214F0
    lw      v1, 0x2C0(s0)
KaleidoScope_Draw_Texture_Logic:
    lui     t6, 0x8012
    lbu     t6, -0x4627(t6)
    lui     a1, 0x8083  ; relocate
    lw      a0, 0x02C0(s0)
    sll     t8, t6, 2
    addu    a1, a1, t8
    lw      a1, -0x61C0(a1) ; relocate
    ;logic for loading a0 if needed
    ori     at, zero, 0x13
    slt     at, at, s6
    ori     s6, zero, 0
    beqz    at, KaleidoScope_TexUnchanged
    nop
    lui     a1, hi(ICON_STATIC_GAME_OVER)
    addiu   a1, a1, lo(ICON_STATIC_GAME_OVER)
    lw      a1, 0(a1)
    addiu   a1, a1, 0x2980
KaleidoScope_TexUnchanged:
    sw      zero, 0x10(sp)
    addiu   a2, zero, 0x0098
    b       KaleidoScope_Draw_ContinuePromtHack_return
    nop
kaleidoScope_yOffsetConditionHack:
    slti    at, v0, 20
    beqz    at, 0x808238B0
    nop
kaleidoScope_Set_yOffset:
    lui     at, 0x0001
    ori     at, at, 0x0760
    addu    t0, a0, at
    addiu   t7, zero, 0x0050
    sh      t7, 0x020A(t0)
    b       0x808238B0
    nop
