# allons au ru

.text
start:
    MOVE $2, $3
    NEG $3, $2
    LI $4, 23
    BLT $4, $4, target


boucle:
    NOP
    ADDI $1 , $1 , lunchtime
    NOP
