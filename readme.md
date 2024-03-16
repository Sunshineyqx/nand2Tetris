# 													Nend2Tetris

![image-20240311101636313](readme.assets/image-20240311101636313.png)

# Part 1

## [Reference](https://www.nand2tetris.org/)

[The Chip Set API](https://drive.google.com/file/d/1IsDnH0t7q_Im491LQ7_5_ajV0CokRbwR/view):

![image-20240306163810146](readme.assets/image-20240306163810146.png)

----

## Project 2

利用上一模块中构建的芯片组，我们现在将着手构建一个*加法器*系列--专为数字加法而设计的芯片。然后，我们将向前迈出一大步，构建一个*算术逻辑单元*。算术逻辑单元设计用于执行一整套算术和逻辑运算，是计算机的计算大脑。在本课程的后半部，我们将使用 ALU 作为核心芯片，并在此基础上构建计算机的*中央处理器*（CPU）。由于所有这些芯片都以二进制数（0 和 1）为运算单位，因此我们将从二进制运算的总体概述开始本模块的学习，然后再深入学习 ALU 的构建。

### 1. ALU 

![image-20240306181216271](readme.assets/image-20240306181216271.png)

![image-20240306181309655](readme.assets/image-20240306181309655.png)



---

## [Project 3](https://drive.google.com/file/d/1ArUW8mkh4Kax-2TXGRpjPWuHf70u6_TJ/view)

在构建了计算机的 ALU 之后，本模块将转而构建计算机的主存储器单元，也称为随机存取存储器或 RAM。这项工作将自下而上逐步完成，从初级触发器门到一位寄存器，再到 n 位寄存器，直至一系列 RAM 芯片。与基于组合逻辑的计算机处理芯片不同，计算机的内存逻辑需要基于时钟的顺序逻辑。我们将首先概述这一理论背景，然后构建我们的内存芯片组。

### 1. Bit

![image-20240306163423697](readme.assets/image-20240306163423697.png)

![image-20240306163441668](readme.assets/image-20240306163441668.png)

### 2. Register

![image-20240306164623634](readme.assets/image-20240306164623634.png)

### 3. RAM8

![image-20240306165144246](readme.assets/image-20240306165144246.png)

### 4. RAM64 & RAM512 & RAM4K &RAM16K

![image-20240306172405117](readme.assets/image-20240306172405117.png)

### 5. PC

![image-20240306172434917](readme.assets/image-20240306172434917.png)

### * 6. D-触发器的构建

https://www.coursera.org/learn/build-a-computer/lecture/XtYPq/unit-3-6-perspectives

---

## [Project 4](https://www.coursera.org/learn/build-a-computer/home/week/4)

构建新计算机系统的一个极其重要的方面是**设计低级机器语言或指令集**，通过指令集可以指示计算机做各种事情。事实证明，这可以在计算机本身实际制造之前完成。例如，我们可以编写一个 Java 程序来模拟尚未建成的计算机，然后用它来模拟执行用新机器语言编写的程序。这样的实验可以让我们对新计算机的基本 "外观和感觉 "有一个很好的了解，从而做出改变和改进硬件和语言设计的决定。在本模块中，我们将采用类似的方法，假设 Hack 计算机和机器语言已经制作完成，并使用 Hack 机器语言编写一些低级程序。然后，我们将使用提供的 **CPU 仿真器**（一种计算机程序）来测试和执行我们的程序。这一经历将让你体验到低级编程的乐趣，并对 Hack 计算机平台有一个扎实的实践概述。

### 1. Hack computer 架构

![image-20240308102001593](readme.assets/image-20240308102001593.png)



### 2.  寻址模式

![image-20240308102033131](readme.assets/image-20240308102033131.png)

### 3.  指令集

> A类指令

![image-20240308102122185](readme.assets/image-20240308102122185.png)



> C类指令

![image-20240308102141154](readme.assets/image-20240308102141154.png)

![image-20240308102150339](readme.assets/image-20240308102150339.png)



### 4. 输入/输出

![image-20240308102329118](readme.assets/image-20240308102329118.png)

> 屏幕

![image-20240308102250369](readme.assets/image-20240308102250369.png)

> 键盘

![image-20240308102340145](readme.assets/image-20240308102340145.png)

### 5. 内置的符号

![image-20240308102206295](readme.assets/image-20240308102206295.png)

### 6. 分支

![image-20240308102415762](readme.assets/image-20240308102415762.png)

### 7. 变量

![image-20240308102428492](readme.assets/image-20240308102428492.png)

### 8. 迭代

![image-20240308102513556](readme.assets/image-20240308102513556.png)

![image-20240308102457717](readme.assets/image-20240308102457717.png)

### 9. 指针

![image-20240308102523931](readme.assets/image-20240308102523931.png)

---

### 作业

1.

![image-20240307224216633](readme.assets/image-20240307224216633.png)

2.

![image-20240308100710595](readme.assets/image-20240308100710595.png)

---

## Project 5

让我们回顾一下过去的四个模块：我们构建了一些基本逻辑门（模块 1），然后用它们构建了一个 ALU（模块 2）和一个 RAM（模块 3）。然后，我们玩了低级编程（模块 4），假设整个计算机确实可用。

在本模块中，我们将把所有这些构件组装成一台名为 Hack 的通用 16 位计算机。我们将首先构建 Hack 中央处理器（CPU），然后将 CPU 与 RAM 集成在一起，创建一个能够执行用 Hack 机器语言编写的程序的完整计算机系统。

### 1. 冯-诺依曼架构

![image-20240308163151470](readme.assets/image-20240308163151470.png)

![image-20240308163238230](readme.assets/image-20240308163238230.png)

![image-20240308164321363](readme.assets/image-20240308164321363.png)

### 2. 取指-执行循环

![image-20240308192910123](readme.assets/image-20240308192910123.png)

《指令获取和数据的获取存在内存上的竞争》

![image-20240308201133434](readme.assets/image-20240308201133434.png)

《解决方案》

1.多路复用

![image-20240308201649039](readme.assets/image-20240308201649039.png)

![image-20240308201821610](readme.assets/image-20240308201821610.png)

2.划分内存

![image-20240308202744016](readme.assets/image-20240308202744016.png)

### 3. 中央处理器

![image-20240308202959139](readme.assets/image-20240308202959139.png)

#### CPU接口

![image-20240308215308943](readme.assets/image-20240308215308943.png)

#### CPU实现

![image-20240308220751066](readme.assets/image-20240308220751066.png)

![image-20240308225559576](readme.assets/image-20240308225559576.png)

![image-20240308223657091](readme.assets/image-20240308223657091.png)

![image-20240308224134134](readme.assets/image-20240308224134134.png)

![image-20240308225422230](readme.assets/image-20240308225422230.png)

![image-20240308225527722](readme.assets/image-20240308225527722.png)

### 4. Hack computer

#### CPU Operation

![image-20240309104203384](readme.assets/image-20240309104203384.png)

![image-20240309104828155](readme.assets/image-20240309104828155.png)

#### Memory

![image-20240309104941111](readme.assets/image-20240309104941111.png)

![image-20240309105223945](readme.assets/image-20240309105223945.png)

![image-20240309105654003](readme.assets/image-20240309105654003.png)![image-20240309105732582](readme.assets/image-20240309105732582.png)

#### ROM

![image-20240309110202840](readme.assets/image-20240309110202840.png)

![image-20240309112544246](readme.assets/image-20240309112544246.png)

#### implementation

![image-20240309113310246](readme.assets/image-20240309113310246.png)

### 5.概述

![image-20240309113823573](readme.assets/image-20240309113823573.png)

#### CPU

![image-20240309113930692](readme.assets/image-20240309113930692.png)

![image-20240309113947123](readme.assets/image-20240309113947123.png)

![image-20240309114444284](readme.assets/image-20240309114444284.png)

![image-20240309114514455](readme.assets/image-20240309114514455.png)

#### Memory

![image-20240309114634701](readme.assets/image-20240309114634701.png)

![image-20240309115405838](readme.assets/image-20240309115405838.png)

#### ROM

内置芯片

#### Computer

![image-20240309115825783](readme.assets/image-20240309115825783.png)

---

## Project 6

每台计算机都有一种二进制机器语言和一种符号机器语言，前者将指令写成一串 0 和 1，后者则使用人类友好的助记符来表达指令。**这两种语言的功能完全相同，完全等价。**但是，用汇编语言编写程序要比用二进制语言编写程序容易得多，也安全得多。为了享受这种奢侈，必须有人将我们的符号程序翻译成二进制代码，以便在目标计算机上按原样执行。这项翻译工作由一个名为***汇编程序***的代理完成。装配员可以是一个手动执行翻译的人，也可以是一个自动执行翻译的计算机程序。在本模块和课程的最后一个项目中，我们将学习如何构建一个汇编器。特别是，我们将开发把符号 Hack 程序翻译成二进制代码的能力，以便在 Hack 平台上按原样执行。你们每个人都可以选择两种不同的方式来完成这一壮举：要么使用高级语言实现汇编器，要么使用纸和笔模拟汇编器的运行。在这两种情况下，我们都会就如何完成工作提供详细的指导。

> 符号表

符号/标签 --------> 地址

> 挑战

+ 空格 ---> 忽略
+ 注释/行内注释 ---> 忽略
+ 符号 ---> :heavy_exclamation_mark:**符号表**，多次处理（变量符号、标签符号、预置符号）
+ 指令 ---> 遵循语言规范进行替换/扩展

![image-20240309204824798](readme.assets/image-20240309204824798.png)

#### 汇编器的软件架构

![image-20240309210842660](readme.assets/image-20240309210842660.png)

##### 1.

![image-20240309210902915](readme.assets/image-20240309210902915.png)

![image-20240309211203282](readme.assets/image-20240309211203282.png)

##### 2.

![image-20240309211826811](readme.assets/image-20240309211826811.png)

![image-20240309213510010](readme.assets/image-20240309213510010.png)

##### 3.

![image-20240309213447252](readme.assets/image-20240309213447252.png)

##### 总体逻辑

![image-20240309215446002](readme.assets/image-20240309215446002.png)

#### 实际编程

![image-20240309220810103](readme.assets/image-20240309220810103.png)

![image-20240309222652501](readme.assets/image-20240309222652501.png)

---

# Part 2

![image-20240311101951477](readme.assets/image-20240311101951477.png)

## Project 7

虚拟机

在某些现代语言（尤其是 Java）中，高级代码并不是直接翻译成机器语言的。相反，Java 编译器会将高级源代码翻译成用中间语言编写的代码，以便在称为*虚拟机*的抽象处理层上运行。

在本模块中，我们将开始构建**基于堆栈的虚拟机**。在介绍了虚拟机架构及其虚拟机语言（类似于 Java 的字节码）后，我们将开发一个基本的虚拟机翻译器（类似于 Java 的JVM），用于将虚拟机程序翻译成 Hack 机器语言。

在下一个模块中，我们将把这个基本翻译器扩展为一个完整的虚拟机实现。这个实现反过来将作为我们在课程后面将要开发的双层编译器的后端模块。

![image-20240312133555774](readme.assets/image-20240312133555774.png)

### 1. The Road ahead

![image-20240311171538322](readme.assets/image-20240311171538322.png)

### 2. 程序编译预览

![image-20240311210244649](readme.assets/image-20240311210244649.png)

![image-20240311210223418](readme.assets/image-20240311210223418.png)

### 3. 虚拟机抽象: 堆栈

在目标机器语言和高级语言之前取得很好平衡的一种架构: stack machine.

![image-20240311211209615](readme.assets/image-20240311211209615.png)

![image-20240311211558584](readme.assets/image-20240311211558584.png)

![image-20240311212557108](readme.assets/image-20240311212557108.png)

![image-20240311212821976](readme.assets/image-20240311212821976.png)

![image-20240311213636301](readme.assets/image-20240311213636301.png)

![image-20240311214537981](readme.assets/image-20240311214537981.png)

![image-20240311215629050](readme.assets/image-20240311215629050.png)

### 4.虚拟机抽象: 内存段

> 内存段和内存段命令

![image-20240311221409095](readme.assets/image-20240311221409095.png)

![image-20240311221638785](readme.assets/image-20240311221638785.png)

> 所有的内存段:

![image-20240311221801738](readme.assets/image-20240311221801738.png)

### 5.虚拟机实现: 堆栈

![478c3e1572eddc995b819e3318bc529](readme.assets/478c3e1572eddc995b819e3318bc529.jpg)

![84cc4f8e905df8a5f90213d5c3caca3](readme.assets/84cc4f8e905df8a5f90213d5c3caca3.jpg)

### 6. 虚拟机实现: 内存段

![080ecec0508805d30b0da978afe47d8](readme.assets/080ecec0508805d30b0da978afe47d8-17102209910621.jpg)

![image-20240312132324811](readme.assets/image-20240312132324811.png)

![image-20240312132331621](readme.assets/image-20240312132331621.png)

![image-20240312132435098](readme.assets/image-20240312132435098.png)

![image-20240312132545716](readme.assets/image-20240312132545716.png)

![image-20240312132849459](readme.assets/image-20240312132849459.png)

![image-20240312133402238](readme.assets/image-20240312133402238.png)

### 7. 虚拟机模拟器

![image-20240312134501466](readme.assets/image-20240312134501466.png)

![image-20240312134900430](readme.assets/image-20240312134900430.png)

![image-20240312140432726](readme.assets/image-20240312140432726.png)

![image-20240312144637947](readme.assets/image-20240312144637947.png)

### 8. Hack平台上虚拟机的实现

![image-20240312144959336](readme.assets/image-20240312144959336.png)

![image-20240312145037260](readme.assets/image-20240312145037260.png)

![image-20240312145116670](readme.assets/image-20240312145116670.png)

![image-20240312151639447](readme.assets/image-20240312151639447.png)

![image-20240312151649139](readme.assets/image-20240312151649139.png)

### 9. 虚拟机实现建议

![image-20240312152615457](readme.assets/image-20240312152615457.png)

![image-20240312154318070](readme.assets/image-20240312154318070.png)

![image-20240312154620998](readme.assets/image-20240312154620998.png)

![image-20240312154803435](readme.assets/image-20240312154803435.png)

![image-20240312160259377](readme.assets/image-20240312160259377.png)

### 10. 构建虚拟机翻译器: Part 1

![image-20240312160734975](readme.assets/image-20240312160734975.png)

![image-20240312161438089](readme.assets/image-20240312161438089.png)

---

## Project 8

在上一模块中，我们介绍了虚拟机抽象，并开发了一个基本的虚拟机翻译器来实现虚拟机语言的算术和内存访问命令。在本模块中，我们将通过实现剩余的虚拟机语言分支和函数调用命令来完成虚拟机翻译器。

**分支**和**函数调用**当然是编程理论和实践的主要内容。因此，我们将在本模块开始时概述它们的用法、抽象和实现。这将为本模块的其余部分奠定基础，在这些部分中，我们将完成虚拟机翻译器的规范和实现。

### 1. 程序控制

分支/函数命令

![image-20240314171407470](readme.assets/image-20240314171407470.png)

![image-20240314174626153](readme.assets/image-20240314174626153.png)

### 2. 分支命令

![image-20240315142354864](readme.assets/image-20240315142354864.png)

### 3.函数命令

![image-20240315152806450](readme.assets/image-20240315152806450.png)

### 4. 函数调用与返回

#### 1.实现预览

//call

![image-20240315173815813](readme.assets/image-20240315173815813.png)

//return

![image-20240315173744715](readme.assets/image-20240315173744715.png)

![image-20240315190329890](readme.assets/image-20240315190329890.png)

#### 2. 运行时模拟

![image-20240315194430030](readme.assets/image-20240315194430030.png)

![image-20240315194414667](readme.assets/image-20240315194414667.png)

#### 3. Function call、return实现

![image-20240315195543529](readme.assets/image-20240315195543529.png)

//caller

![image-20240315200035840](readme.assets/image-20240315200035840.png)

//callee

![image-20240315200631035](readme.assets/image-20240315200631035.png)

//**实现！！！！**

call

![image-20240315203232253](readme.assets/image-20240315203232253.png)

function

![image-20240315203539428](readme.assets/image-20240315203539428.png)

return

![image-20240315204213072](readme.assets/image-20240315204213072.png)

![image-20240315204223054](readme.assets/image-20240315204223054.png)

---

![image-20240315204433827](readme.assets/image-20240315204433827.png)

---

#### 4. 在Hack平台上实现虚拟机

![image-20240315231630071](readme.assets/image-20240315231630071.png)

![image-20240315233033686](readme.assets/image-20240315233033686.png)

![image-20240315233420377](readme.assets/image-20240315233420377.png)

![image-20240315233620132](readme.assets/image-20240315233620132.png)

//

![image-20240315234708508](readme.assets/image-20240315234708508.png)

![image-20240315234737373](readme.assets/image-20240315234737373.png)

![image-20240315234745006](readme.assets/image-20240315234745006.png)

![image-20240315234759486](readme.assets/image-20240315234759486.png)
