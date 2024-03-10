#ifndef Parser_H
#define Parser_H

#include <iostream>
#include <string>
#include <fstream>

class Parser{
public:
	Parser(std::string& filename);
	~Parser();

	bool hasMoreCommands();
	void advance();
	std::string comp();
	std::string dest();
	std::string jump();
private:
	std::ifstream asm_file;
	int lineNum;
};

#endif // Parser_H