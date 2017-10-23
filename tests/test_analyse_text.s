# test analyse_text

NOP3 $4, $4, $5
NOP3 $3, $4
NOP3 $3, 4 $5

NOP2 $1, $3, $5
NOP2
NOP2 4, 4

NOP1 23
NOP1 23, 23

INVALID_INSTRU $2

#force ERROR_MSG
error: 0x345 $33
