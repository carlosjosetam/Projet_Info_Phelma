.data
.space 1234
.space 12
.byte 8
.byte abcdf
.byte 0x123
.word 2344443423
.word "salut"
.word ASDFS
.word 0x123
.asciiz "flango"
.asciiz 1234

.text
ADD ,$7, $8, $9
ADD 4
ADD $7 $3 4343
ADD $7, $8, $9
MOV 323, hued
MOVS 2

.bss
menu: .space 24
.space 0x33
.space a
.space 3
.space 2
.space 200
.space 127
