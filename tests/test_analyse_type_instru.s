# test analyse_coll
# on veut tester qui le push
# aux collections marche bien

start: NOP3 $1, $2, $3
NOP3 $1, $2, $3
NOP2 $1, $2

.data
.space  24
.byte 0x66
.word 234
.asciiz "bonjour"

.text
NOP1 0x678f

.data
lunchtime: .word 12
.word menu

.bss
menu: .space 24
exit: .space 33
