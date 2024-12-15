KaleidoScopeCall_Draw:
    addiu   sp, sp, 0xFFE8           
    sw      ra, 0x0014(sp)
    lui     t6, 0x8012                 
    lw      t6, -0x4600(t6)            
    lui     v0, 0x0001                 
    addu    v0, v0, a0
    lh      t7, 0x0190(t6)             
    slti    at, t7, 0x0003
    bnel    at, zero, lbl_8009A15C
    lw      ra, 0x0014(sp)
    lhu     v0, 0x0934(v0)             
    slti    at, v0, 0x0004
    bne     at, zero, new_condition_check
    slti    at, v0, 0x0008
    bne     at, zero, lbl_8009A134
new_condition_check:
    ori     at, zero, 0x14
    beq     at, v0, lbl_8009A134
    addiu   at, at, 1
    beq     at, v0, lbl_8009A134
    addiu   at, at, 2
    beq     at, v0, lbl_8009A134
    nop
lbl_8009A124:
    slti    at, v0, 0x000B
    bne     at, zero, lbl_8009A158
    slti    at, v0, 0x0013
    beq     at, zero, lbl_8009A158
lbl_8009A134:
    lui     t9, 0x8010                 
    lw      t9, -0x1B44(t9)            
    lui     t8, 0x8010                 
    addiu   t8, t8, 0xE480             
    bne     t8, t9, lbl_8009A158
    lui     t9, 0x8012                 
    lw      t9, -0x2FBC(t9)            
    jalr    t9, ra
    nop
lbl_8009A158:
    lw      ra, 0x0014(sp)
lbl_8009A15C:
    addiu   sp, sp, 0x0018           
    jr      ra
    nop
    nop
    nop

ICON_STATIC_GAME_OVER:
.word 0x00000000

CFG_SAVE_AND_QUIT:
.byte 0x00

.align 0x10
CONTINUE_PROMPT_TEX:
.area 0x980, 0
.endarea