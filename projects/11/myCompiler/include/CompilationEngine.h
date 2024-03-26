#ifndef COMPILATIONENGINE_H
#define COMPILATIONENGINE_H

#include "./JackTokenizer.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class CompilationEngine{
public:
    CompilationEngine(JackTokenizer* tokenizer, const string& outFilePath);
    ~CompilationEngine();

    void compileClass(void); // Compiles a complete class
	void compileClassVarDec(void); // Compiles a static declaration or a field declaration
	void compileSubroutine(void); // Compiles a complete method, function, or constructor
	void compileParameterList(void); // Compiles a (possibly empty) parameter list, not including the enclosing "()"
	void compileSubroutineBody(void); // Compiles subroutine body
	void compileVarDec(void); // Compiles a var declaration
	void compileStatements(void); // Compiles a sequence of statements, not including the enclosing {}.
	void compileDo(void); // Compiles a do statement
	void compileLet(void); // Compiles a let statement
	void compileWhile(void); // Compiles a while statement
	void compileReturn(void); // Compiles a return statement
	void compileIf(void); // Compiles an if statement, possible with a trailing else clause
	void compileExpression(void); // Compiles an expression
	void compileTerm(void); // Compiles a term.  Uses a single lookahead
	void compileExpressionList(void); // Compiles a (possibly empty) comma-separated list of expressions
    
private:
    JackTokenizer* _JT;
    ofstream outFile;
};


#endif // COMPILATIONENGINE