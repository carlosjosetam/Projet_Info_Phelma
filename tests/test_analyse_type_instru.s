# test analyse_type_instruction
# all samples concerned here have the right number of operands

# here all samples work
ADD $1, $2, $3

ADDI $2, $t3, 200
ADDI $2, $3, 0x3f
ADDI $2, $3, X

LW $2, 200($3)
SLL $2, $3, 12
MFHI $t1
BEQ $zero, $t2, -0x200($3)

# here we have problems
ADD $2, $2, 2
ADDI $2, $2, $3

LW zero, 1234

BEQ 123, 456, $3
