; Pause screen

.headersize(0x808137C0 - 0x00BB11E0)

.org 0x808264dc
    ;Replaces
    ; ori     $at, $at, 0x0760           # $at = 00010760
    ; addu    s0, s1, $at
    ; lhu     t8, 0x01D4(s0)             # 000001D4
    ; addiu   t9, t8, 0xFFFD             # t9 = FFFFFFFD
    ; sltiu   $at, t9, 0x0011
    ; beq     $at, $zero, lbl_80828BE4
    ; sll     t9, t9,  
    b       0x80827690
    ori     at, at, 0x760
    nop
    nop
    nop
    nop
    nop
    ; lui     $at, %hi(var_8082E68C)     # $at = 80830000
    ; addu    $at, $at, t9
    ; lw      t9, %lo(var_8082E68C)($at)
    ; jr      t9
    ; nop


.org 0x8081E978
   ;jal     KaleidoScope_UpdatePrompt
   ;nop
   ;lw      ra, 0x001c(sp)
   ;jr      ra
   ;addiu   sp, sp, 0x0038

.org 0x80827668
    lui     a0, 0x801C
    jal     kaleidoScope_Case7
    addiu   a0, a0, 0x84A0
    b       0x80828BE4
    nop

.org 0x80827690
    addu    s0, s1, at
    lhu     t8, 0x01D4(s0)
    lui     at, 0
    addiu   at, at, 20
    beq     t8, at, @@case20 
    addiu   at, at, 1
    beq     t8, at, @@case21
    addiu   at, at, 1
    beq     t8, at, @@case22
    addiu   t9, t8, 0xFFFD
    sltiu   at, t9, 0x0011
    beq     at, zero, 0x80828BE4
    sll     t9, t9, 0x0002
    b       0x808264f4
    nop
@@case20:
    lui     a0, 0x801C
    jal     kaleidoScope_Case20
    addiu   a0, a0, 0x84A0
    b       0x80828BE4
    nop
@@case21:
    lui     a0, 0x801C
    jal     kaleidoScope_Case21
    addiu   a0, a0, 0x84A0
    b       0x80828BE4
    nop
@@case22:
    ; i think this is the offset of case 17  (update: it is)
    b       0x808287D8
    nop