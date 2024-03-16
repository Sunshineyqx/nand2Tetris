//push constant 0
@0
D = A
@SP
A = M
M = D
@SP
M = M + 1

//pop local 0
@LCL
D = M
@0
D = D + A
@R13
M = D
@SP
M = M - 1
@SP
A = M
D = M
@R13
A = M
M = D

//label LOOP
(LOOP)

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

//pop local 0
@LCL
D = M
@0
D = D + A
@R13
M = D
@SP
M = M - 1
@SP
A = M
D = M
@R13
A = M
M = D

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

//push constant 1
@1
D = A
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

//pop argument 0
@ARG
D = M
@0
D = D + A
@R13
M = D
@SP
M = M - 1
@SP
A = M
D = M
@R13
A = M
M = D

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

//if-goto LOOP        
@SP
M = M - 1
@SP
A = M
D = M
@LOOP        
D;JNE

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

