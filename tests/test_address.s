# allons au ru

.text
    ADD $3, $3, $5
    LW $6, -0x200($7)
    ADDI $1, $zero, lunchtime

boucle:
    NOP
    ADDI $1 , $1 , lunchtime
    NOP
byebye:
    ADD $1, $2, $3

.data
lunchtime: .word 12
.word menu

.bss
menu:.space 24
