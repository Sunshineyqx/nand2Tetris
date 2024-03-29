#ifndef VMWRITER_H_
#define VMWRITER_H_
#include <string>
#include <fstream>
using namespace std;

namespace vmwriter
{
	enum Segment { CONST, ARG, LOCAL, STATIC, THIS, THAT, POINTER, TEMP, UNKNOWN };
	enum Command { ADD, SUB, NEG, EQ, GT, LT, AND, OR, NOT };
	
	string segment2String(Segment seg);
	
	string command2String(Command com);
};
namespace vm=vmwriter;

class VMWriter{
public:
    VMWriter(string filePath);

    void writePush(vm::Segment segment, int index); // Writes a VM push command
	void writePop(vm::Segment segment, int index); // Writes a VM pop command
	void writeArithmetic(vm::Command command); // Writes a VM arithmetic command
	void writeLabel(string label); // Writes a VM label command
	void writeGoto(string label); // Writes a VM goto command
	void writeIf(string label); // Writes a VM if-goto command
	void writeCall(string name, int nArgs); // Writes a VM call command
	void writeFunction(string name, int nLocals); // Writes a VM function command
	void writeReturn(void); // Writes a VM return command
	void close(void); // Closes the output file
	string getFileName() {return fileName_;}

private:
    ofstream fout_;
	string fileName_;
};


#endif // VMWRITER_