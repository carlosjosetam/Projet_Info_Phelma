ADD $4, $5, $6
etiq:.test assemos
SUBS $4:3,$5,$5 #COMENTAIRE
SUBS $4,0xwe,0x123 123f #COMENTAIRE
SUB#S $4,$5 , $6
lalala #COMENTAIRE

.set noreorder
.text
ADD $1, $2, $3   #un com
LW $6,-0x200($7)

.data
lunch : .word 12
.byte 2, 0x4

.bss
.space 12

ADD "salut","ciao"
ADD  "salut","ciao" ..data
.word .wwwwwwwww uuuuuuu
.word 12
