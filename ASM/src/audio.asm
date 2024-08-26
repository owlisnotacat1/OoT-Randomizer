@fanfare_audioseq_size equ 0x1000
@fanfare_audiobank_size equ 0x4800
@fanfare_unk_size equ 0
@bgm_audioseq_size equ 0xE000
@bgm_audiobank_size equ 0x4800
@bgm_unk_size equ 0

@adsrstate_sub_size equ 0x320

AUDIO_THREAD_MEM_SIZE equ \
(0x37F00 - 0x6670 + @fanfare_audioseq_size + @fanfare_audiobank_size + @bgm_audioseq_size + @bgm_audiobank_size)



AUDIO_THREAD_INFO:
.word \
@fanfare_audioseq_size,     \
@fanfare_audiobank_size,    \
@fanfare_unk_size,          \
@bgm_audioseq_size,         \
@bgm_audiobank_size,        \
@bgm_unk_size

.align 0x8 //force hi() to always be the same for both vars
AUDIO_THREAD_INFO_MEM_START:
.word AUDIO_THREAD_MEM_START
AUDIO_THREAD_INFO_MEM_SIZE:
.word AUDIO_THREAD_MEM_SIZE

.align 0x10
AUDIOBANK_TABLE_EXTENDED:
.area 0xA00, 0
.endarea

FONTLOADSTATUS_EXTENDED:
.area 0xA0, 0
.endarea

ADSR_SUB_DATA:
.area 0x04, 0
.endarea

.align 0x10
; Hack for when AudioLoad_SyncLoadFont checks fontLoadStatus
; Put the address to load into T6
AudioLoad_SyncLoadFont_StatusHack:
    addiu   a1, a1, 0x5630 ; Replaced code
    li      t6, FONTLOADSTATUS_EXTENDED
    jr      ra
    addu    t6, t6, v0


//used to calculate the remaining free size of the audio thread heap
get_audio_pointers:
    li      t9, @fanfare_audioseq_size
    li      t2, @fanfare_audiobank_size
    li      t5, @fanfare_unk_size
    li      t4, @bgm_audioseq_size
    li      t6, @bgm_audiobank_size
    jr      ra
    li      t8, @bgm_unk_size

// allocates area of memory for AdsrState->sub chunk and returns a pointer to it to gAdsrSubDataAddress
AudioHeap_Init_AdsrSubData:
    addiu   $sp, $sp, -0x0010
    sw      $ra, 4($sp)
    lui     t3, 0x8012
    addiu   t3, t3, 0x7FF0 ; loads address of gAudioCtx.miscPool into s3 to be moved to a0
    lui     a1, 0x0000
    addiu   a1, 0x0320 ; loads size of area being allocated into a1
    jal     0x800B3940
    move    a0, t3
    lui     t3, hi(ADSR_SUB_DATA)
    addiu   t3, lo(ADSR_SUB_DATA)
    sw      v0, 0x0000(t3)
    lw      $ra, 4($sp)
    addiu   $sp, $sp, 0x0010
    jr      $ra
    nop



