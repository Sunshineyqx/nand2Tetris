#include <iostream>
#include <fstream>
#include "../include/Parser.h"
#include "../include/Code.h"
#include "../include/SymbolTable.h"
using namespace std;



int main(int argc, char *argv[]){
    
    if(argc != 2){
        cerr << "Usage: " << argv[0] << "<inputfilename.asm>" <<endl;
        exit(1);
    }

    string inputFileName = argv[1];
    string outputFileName = inputFileName.substr(0, inputFileName.length() - 4) + ".hack";
    //全局符号表
    SymbolTable symbolTable; 

    //第一次pass,添加标签符号
    int real_line = 0;
    Parser labelParser(inputFileName);
    while(labelParser.hasMoreCommands()) {
        labelParser.advance();
        if(labelParser.instructionType() == A_INSTRUCTION || labelParser.instructionType() == C_INSTRUCTION) {
            real_line++;
        }
        if(labelParser.instructionType() == L_INSTRUCTION && !symbolTable.isContained(labelParser.symbol())) {
            symbolTable.addEntry(labelParser.symbol(), real_line);
        }
    }
    //第2次pass
    Parser parser(inputFileName);
    Code code;
    ofstream out(outputFileName);
    size_t var_address = 16;
    while(parser.hasMoreCommands()){
        parser.advance();
        if(parser.instructionType() == A_INSTRUCTION){
            string a =  parser.symbol();
            //数字
            if (a.find_first_not_of("0123456789") == string::npos){
                out << "0" <<code.processA(a) << endl;    
            }
            else if(symbolTable.isContained(a)){ //标签符号
                int address = symbolTable.getAddress(a);
                out << "0" <<code.processA(address) << endl;    
            }
            else{ //变量符号
                symbolTable.addEntry(a, var_address);
                out << "0" << code.processA(var_address) << endl;
                var_address++;
            }
        }
        else if(parser.instructionType() == C_INSTRUCTION){
            string dest =  parser.dest();
            string comp =  parser.comp();
            string jump =  parser.jump();
            string res = "111" + code.comp(comp) + code.dest(dest) + code.jump(jump);
            out << res << endl;
        }
        else{ //  (label) 在此忽略
            continue;
        }
    }
    out.close();
}