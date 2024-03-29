#include "../include/VMWriter.h"

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;

string vm::segment2String(Segment seg)
	{
		switch(seg)
		{
			case CONST:
				return "constant";
			case ARG:
				return "argument";
			case LOCAL:
				return "local";
			case STATIC:
				return "static";
			case THIS:
				return "this";
			case THAT:
				return "that";
			case POINTER:
				return "pointer";
			case TEMP:
				return "temp";
			default:
				return "unknown";
		}
	}

string vm::command2String(Command com)
{
		switch(com)
		{
			case ADD:
				return "add";
			case SUB:
				return "sub";
			case NEG:
				return "neg";
			case EQ:
				return "eq";
			case GT:
				return "gt";
			case LT:
				return "lt";
			case AND:
				return "and";
			case OR:
				return "or";
			case NOT:
				return "not";
			default:
				return "unknown";
		}
}


VMWriter::VMWriter(string filePath)
{	
	fout_.open(filePath.c_str());
	//去掉文件路径的前后缀
	std::filesystem::path file(filePath);
    fileName_ = file.stem().string();
}

void VMWriter::close(void)
{
	if(fout_.is_open())
		fout_.close();
}

void VMWriter::writePush(vm::Segment segment, int index)
{
	fout_ << "push " << vm::segment2String(segment) << " " << index << endl;
}

void VMWriter::writePop(vm::Segment segment, int index)
{
	fout_ << "pop " << vm::segment2String(segment) << " " << index << endl;
}

void VMWriter::writeArithmetic(vm::Command command)
{
	fout_ << vm::command2String(command) << endl;
}

void VMWriter::writeLabel(string label)
{
	fout_ << "label " << label << endl;
}

void VMWriter::writeGoto(string label)
{
	fout_ << "goto " << label << endl;
}

void VMWriter::writeIf(string label)
{
	fout_ << "if-goto " << label << endl;
}

void VMWriter::writeCall(string name, int nArgs)
{
	fout_ << "call " << name << " " << nArgs << endl;
}

void VMWriter::writeFunction(string name, int nLocals)
{
	fout_ << "function " << name << " " << nLocals << endl;
}

void VMWriter::writeReturn(void)
{
	fout_ << "return" << endl;
}