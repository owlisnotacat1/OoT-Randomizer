; Pause screen

.headersize(0x808137C0 - 0x00BB11E0)

.org 0x808264dc
    ;Replaces
    ; ori   $at, $at, 0x0760           # $at = 00010760
    ; addu  s0, s1, $at
    ; lhu   t8, 0x01D4(s0)             # 000001D4
    ; addiu t9, t8, 0xFFFD             # t9 = FFFFFFFD
    ; sltiu $at, t9, 0x0011
    ; beq   $at, $zero, lbl_80828BE4
    ; sll   t9, t9,  
    
    b       0x80827690              ; this branch is to a modified version of the pauseCtx->state switch case
    ori     at, at, 0x760           ; replaced code 
    nop
    nop
    nop
    nop
@@return:
    nop
    ; lui   $at, %hi(var_8082E68C)     # $at = 80830000
    ; addu  $at, $at, t9
    ; lw    t9, %lo(var_8082E68C)($at)
    ; jr    t9
    ; nop

.org 0x80820d94
    b       KaleidoScope_DrawPages_ConditionHack
    nop
KaleidoScope_DrawPages_ConditionHack_return:
    nop

; offset 1BF30
; nop out mips 26 abi relocation for call to KaleidoScope_UpdatePrompt
.org 0x8082F6F0
    ;.word 0x00000000

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


.org 0x80827690
    addu    s0, s1, at              
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
    ; i think this is the offset of case 17  (update: it is)
    b       0x808287D8              ; jumps to case 17
    nop
KaleidoScope_DrawPages_ConditionHack:
    li      at, 7
    beq     a0, at, 0x80820db0
    li      at, 21
    beq     a0, at, 0x80820db0
    li      at, 20
    beq     a0, at, 0x80820db0
    nop
    b       KaleidoScope_DrawPages_ConditionHack_return
    nop
    
