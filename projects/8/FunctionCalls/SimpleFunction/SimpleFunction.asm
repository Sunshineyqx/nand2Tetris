//function SimpleFunction.test 2
(SimpleFunction.test)
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1

//push local 0
@LCL
D = M
@0
D = D + A
A = D
D = M
@SP
A = M
M = D
@SP
M = M + 1

//push local 1
@LCL
D = M
@1
D = D + A
A = D
D = M
@SP
A = M
M = D
@SP
M = M + 1

//add
@SP
M = M - 1
@SP
A = M
D = M
@SP
M = M - 1
@SP
A = M
D = D + M
@SP
A = M
M = D
@SP
M = M + 1

//not
@SP
M = M - 1
@SP
A = M
D = M
D = !D
@SP
A = M
M = D
@SP
M = M + 1

//push argument 0
@ARG
D = M
@0
D = D + A
A = D
D = M
@SP
A = M
M = D
@SP
M = M + 1

//add
@SP
M = M - 1
@SP
A = M
D = M
@SP
M = M - 1
@SP
A = M
D = D + M
@SP
A = M
M = D
@SP
M = M + 1

//push argument 1
@ARG
D = M
@1
D = D + A
A = D
D = M
@SP
A = M
M = D
@SP
M = M + 1

//sub
@SP
M = M - 1
@SP
A = M
D = M
@SP
M = M - 1
@SP
A = M
D = M - D
@SP
A = M
M = D
@SP
M = M + 1

//return
@LCL
D = M
@R13
M = D
@5
A = D - A
D = M
@R14
M = D
@SP
M = M - 1
@SP
A = M
D = M
@ARG
A = M
M = D
@ARG
D = M + 1
@SP
M = D
@R13
D = M
D = D - 1
A = D
D = M
@THAT
M = D
@R13
D = M
@2
D = D - A
A = D
D = M
@THIS
M = D
@R13
D = M
@3
D = D - A
A = D
D = M
@ARG
M = D
@R13
D = M
@4
D = D - A
A = D
D = M
@LCL
M = D
@R14
A = M
0;JMP

