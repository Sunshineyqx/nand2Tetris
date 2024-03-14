#include "../include/Parser.h"
#include "../include/CodeWriter.h"


int main(int argc, char* argv[]){

    if(argc != 2) {
        cerr << "Usage: " << argv[0] << " "<< "<input file name>"<<endl;
        exit(1);
    }
    Parser parser("./mytest.vm");
    CodeWriter codeWriter("./mytest.asm");
    //cout << parser.RemoveSpaceAndComment("Push hello n //sadad") << endl;
    while(parser.hasMoreCommands()){
        parser.advance();
        codeWriter.WriteComment(parser.curCommand());
        if(parser.commandType() == Parser::Command::C_ARITHMETIC){
            codeWriter.WriteArithmetic(parser.cmd());
        }
        else if(parser.commandType() == Parser::Command::C_PUSH or parser.commandType() == Parser::Command::C_POP){
            codeWriter.WritePushPop(parser.cmd(), parser.arg1(), parser.arg2());
        }
        else{
            cout << "main(): unknown command:" <<"*"<<parser.curCommand() <<"*"<<endl;
            break;
        }
    }
    return 0;
}