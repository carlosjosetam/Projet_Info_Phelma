# allons au ru

.text
start:
    ADD $3, $3, $6
    LW $6, -0x200($7)
    ADDI $1, $zero, lunchtime
    ADDI $1, $2, notDeclared

boucle:
    NOP
    ADDI $1 , $1 , 0123
    NOP
    J 671088642
    J boucle
byebye:
    ADD $1, $2, $3
    ADDI $1, $2, start

.data
lunchtime: .word 12
.word menu

.bss
menu:.space 24
