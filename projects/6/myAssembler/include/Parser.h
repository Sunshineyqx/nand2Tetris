#ifndef Parser_H
#define Parser_H

#include <iostream>
#include <string>
#include <fstream>

enum InstructionType {
		A_INSTRUCTION, C_INSTRUCTION, L_INSTRUCTION
};//命令类型

class Parser{
public:
	Parser(const std::string& filename);
	~Parser();

	bool hasMoreCommands(); //是否还有更多的命令
	bool advance(); //当还有更多命令时，将命令写入cur_instruction
	enum InstructionType instructionType();

	//返回A命令的助记符形式或者标签符号
	std::string symbol();
	//返回C命令的助记符形式
	std::string comp();
	std::string dest();
	std::string jump();
public:
	size_t get_lineNum() {return cur_lineNum;}

private:
	std::ifstream asm_file; //输入文件流
	size_t cur_lineNum; //当前行号
	std::string cur_instruction; //当前指令


};

#endif // Parser_H