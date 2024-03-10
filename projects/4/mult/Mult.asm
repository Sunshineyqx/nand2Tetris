// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

// Usage: R0 >=0 && R1 >= 0 && R0 * R1 <= 2^15 -1
//// Replace this comment with your code.

//利用加法实现乘法:

//变量初始化
@R0
D = M
@a
M = D // a = R[0]

@R1
D = M
@b
M = D // b = R[1]

@R2
M = 0 // R[2] = 0

@i
M = 0 // i = 0

(LOOP)
@i
D = M // D = i
@b
D = M - D // D = i - b
@END
D;JEQ

@a
D = M // D = a
@R2
M = D + M //R[2] = R[2] + a
@i
M = M + 1 // i = i + 1
@LOOP
0;JMP

(END)
@END
0;JEQ

