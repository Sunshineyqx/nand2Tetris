// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//// Replace this comment with your code.
//Usage:
//外层循环用于确定是否有按键，来决定将像素设为0/1
//内层循环 设置全部像素值

//变量初始化
@8192
D = A
@n
M = D // n = 8192

(LOOP1)
@pixel
M = 0 //pixel = 0

@i
M = 0 // i = 0

@SCREEN
D = A
@addr
M = D // addr = SCREEN

@KBD
D = M // D = RAM[KBD]

@LOOP2
D;JEQ // D == 0，跳转LOOP2

@pixel
M = -1 // pixel = -1

(LOOP2)
@i
D = M
@n
D = D - M
@LOOP1
D;JEQ  // if(i == n) goto LOOP1

@pixel
D = M  //D = pixel

@addr
A = M
M = D   // RAM[addr] = pixel

@addr
M = M + 1   // addr = addr + 1

@i
M = M + 1 // i = i + 1

@LOOP2
0;JMP




