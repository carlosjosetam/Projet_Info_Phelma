# test analyse_type_instruction
# all samples concerned here have the right number of operands

# here all samples work
ADD $1, $2, $3

ADDI $2, $3, 200
ADDI $2, $3, 0x3f
ADDI $2, $3, X

LW $2, 200($3)
SLL $2, $3, 12
MFHI $1
BEQ $zero, $2, -0x200($3)

#problems
ADDI $2, $3, 0x3FFF45
