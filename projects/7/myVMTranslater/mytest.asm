//push constant 17
@17
D = A
@SP
A = M
M = D
@SP
M = M + 1

//push constant 17
@17
D = A
@SP
A = M
M = D
@SP
M = M + 1

//eq
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
@TrueLabel0
D;JEQ
@SP
A = M
M = 0
@EndLabel0
0;JMP
(TrueLabel0)
@SP
A = M
M = -1
(EndLabel0)
@SP
M = M + 1

//push constant 17
@17
D = A
@SP
A = M
M = D
@SP
M = M + 1

//push constant 16
@16
D = A
@SP
A = M
M = D
@SP
M = M + 1

//eq
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
D;JEQ
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

//push constant 16
@16
D = A
@SP
A = M
M = D
@SP
M = M + 1

//push constant 17
@17
D = A
@SP
A = M
M = D
@SP
M = M + 1

//eq
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
@TrueLabel2
D;JEQ
@SP
A = M
M = 0
@EndLabel2
0;JMP
(TrueLabel2)
@SP
A = M
M = -1
(EndLabel2)
@SP
M = M + 1

//push constant 892
@892
D = A
@SP
A = M
M = D
@SP
M = M + 1

//push constant 891
@891
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
@TrueLabel3
D;JLT
@SP
A = M
M = 0
@EndLabel3
0;JMP
(TrueLabel3)
@SP
A = M
M = -1
(EndLabel3)
@SP
M = M + 1

//push constant 891
@891
D = A
@SP
A = M
M = D
@SP
M = M + 1

//push constant 892
@892
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
@TrueLabel4
D;JLT
@SP
A = M
M = 0
@EndLabel4
0;JMP
(TrueLabel4)
@SP
A = M
M = -1
(EndLabel4)
@SP
M = M + 1

//push constant 891
@891
D = A
@SP
A = M
M = D
@SP
M = M + 1

//push constant 891
@891
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
@TrueLabel5
D;JLT
@SP
A = M
M = 0
@EndLabel5
0;JMP
(TrueLabel5)
@SP
A = M
M = -1
(EndLabel5)
@SP
M = M + 1

//push constant 32767
@32767
D = A
@SP
A = M
M = D
@SP
M = M + 1

//push constant 32766
@32766
D = A
@SP
A = M
M = D
@SP
M = M + 1

//gt
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
@TrueLabel6
D;JGT
@SP
A = M
M = 0
@EndLabel6
0;JMP
(TrueLabel6)
@SP
A = M
M = -1
(EndLabel6)
@SP
M = M + 1

//push constant 32766
@32766
D = A
@SP
A = M
M = D
@SP
M = M + 1

//push constant 32767
@32767
D = A
@SP
A = M
M = D
@SP
M = M + 1

//gt
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
@TrueLabel7
D;JGT
@SP
A = M
M = 0
@EndLabel7
0;JMP
(TrueLabel7)
@SP
A = M
M = -1
(EndLabel7)
@SP
M = M + 1

//push constant 32766
@32766
D = A
@SP
A = M
M = D
@SP
M = M + 1

//push constant 32766
@32766
D = A
@SP
A = M
M = D
@SP
M = M + 1

//gt
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
@TrueLabel8
D;JGT
@SP
A = M
M = 0
@EndLabel8
0;JMP
(TrueLabel8)
@SP
A = M
M = -1
(EndLabel8)
@SP
M = M + 1

//push constant 57
@57
D = A
@SP
A = M
M = D
@SP
M = M + 1

//push constant 31
@31
D = A
@SP
A = M
M = D
@SP
M = M + 1

//push constant 53
@53
D = A
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

//push constant 112
@112
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

//neg
@SP
M = M - 1
@SP
A = M
D = M
D = -D
@SP
A = M
M = D
@SP
M = M + 1

//and
@SP
M = M - 1
@SP
A = M
D = M
@SP
M = M - 1
@SP
A = M
D = D & M
@SP
A = M
M = D
@SP
M = M + 1

//push constant 82
@82
D = A
@SP
A = M
M = D
@SP
M = M + 1

//or
@SP
M = M - 1
@SP
A = M
D = M
@SP
M = M - 1
@SP
A = M
D = D | M
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

