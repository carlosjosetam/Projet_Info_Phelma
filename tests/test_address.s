# allons au ru

.text
    ADD $3, $3, $5
    LW $6, -0x200($7)
    ADDI $1, $zero ,8

boucle:
    NOP
    ADDI $1 , $1 , 1
    # J boucle
    NOP
byebye:
    # JAL viteviteauru

.data
lunchtime: .word 12
.word menu

.bss
menu:.space 24
