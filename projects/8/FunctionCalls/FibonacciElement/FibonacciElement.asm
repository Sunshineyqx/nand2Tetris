//bootstrap
@261
D=A
@SP
M=D
@Sys.init
0;JMP

//function Sys.init 0
(Sys.init)

//push constant 4
@4
D = A
@SP
A = M
M = D
@SP
M = M + 1

//call Main.fibonacci 1
@Main.fibonacciret.0
D = A
@SP
A = M
M = D
@SP
M = M + 1
@LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
@ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THAT
D = M
@SP
A = M
M = D
@SP
M = M + 1
@SP
D = M
@6
D = D - A
@ARG
M = D
@SP
D = M
@LCL
M = D
@Main.fibonacci
0;JMP
(Main.fibonacciret.0)

//label END
(END)

//goto END
@END
0;JMP

//function Main.fibonacci 0
(Main.fibonacci)

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

//push constant 2
@2
D = A
@SP
A = M
M = D
@SP
M = M + 1

//lt
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
@TrueLabel1
D;JLT
@SP
A = M
M = 0
@EndLabel1
0;JMP
(TrueLabel1)
@SP
A = M
M = -1
(EndLabel1)
@SP
M = M + 1

//if-goto N_LT_2
@SP
M = M - 1
@SP
A = M
D = M
@N_LT_2
D;JNE

//goto N_GE_2
@N_GE_2
0;JMP

//label N_LT_2
(N_LT_2)

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

//label N_GE_2
(N_GE_2)

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

//push constant 2
@2
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

//call Main.fibonacci 1
@Main.fibonacciret.2
D = A
@SP
A = M
M = D
@SP
M = M + 1
@LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
@ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THAT
D = M
@SP
A = M
M = D
@SP
M = M + 1
@SP
D = M
@6
D = D - A
@ARG
M = D
@SP
D = M
@LCL
M = D
@Main.fibonacci
0;JMP
(Main.fibonacciret.2)

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

//call Main.fibonacci 1
@Main.fibonacciret.3
D = A
@SP
A = M
M = D
@SP
M = M + 1
@LCL
D = M
@SP
A = M
M = D
@SP
M = M + 1
@ARG
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THIS
D = M
@SP
A = M
M = D
@SP
M = M + 1
@THAT
D = M
@SP
A = M
M = D
@SP
M = M + 1
@SP
D = M
@6
D = D - A
@ARG
M = D
@SP
D = M
@LCL
M = D
@Main.fibonacci
0;JMP
(Main.fibonacciret.3)

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

