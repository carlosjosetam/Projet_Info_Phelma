# test analyse_data

.data
.space 1234, 234 #com
.byte 8
.byte abcdf
etiq: .byte 0x123
.word 2344443423
etiq2: .word "salut"
.word ASDFS
.word 0x123
etiq3: .asciiz "flango"
.asciiz 1234
# to generate ERROR_MSG
ADD $4, $5, $5
