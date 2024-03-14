#include "../include/Parser.h"
#include <algorithm>

Parser::Parser(const string &filePath): inFile(filePath, ios::in),fileName(filePath)
{
    if(!inFile.is_open()){
        cout << "Parser(const string& filePath) : 文件打开失败"<<endl;
    }
}

Parser::~Parser()
{
    inFile.close();
}

bool Parser::hasMoreCommands()
{
    return !inFile.eof();
}
void Parser::commandClear(){
    command.cmd = "";
    command.arg1 = "";
    command.arg2 = -1;
    command.type = Parser::Command::C_UNKONWN;
}
void Parser::advance(){
    commandClear();
    string line;
    while(hasMoreCommands()){
        getline(inFile, line);
        string tmpLine = RemoveComment(line);
        //cout << "0.line:"  << line << endl;
        if(tmpLine.empty() || tmpLine.size() == 0 || tmpLine.size() == 1) continue;
        if(tmpLine.find("\r") != string::npos) { tmpLine = tmpLine.substr(0,  tmpLine.size() - 1);} //有必要么
        //cout << "1.tmpLine:"  <<tmpLine << endl;
        string str1, str2, str3;
        //Memory access commands: push n ; pop n
        if(tmpLine.find("push") != string::npos || tmpLine.find("pop") != string::npos){
            auto index1 = tmpLine.find_first_of(" ");
            auto index2 = tmpLine.find_first_of(" ", index1 + 1);
            str1 = tmpLine.substr(0, index1);
            str2 = tmpLine.substr(index1 + 1, index2 - (index1 + 1));
            str3 = tmpLine.substr(index2 + 1);
            //cout << "2.内存访问指令:*"<< str1 << "*"<< str2 <<  "*"<<str3 <<"*"<<endl;
            if(str1 == "push"){
                command.type = Command::CmdType::C_PUSH;
            }
            else if(str1 == "pop"){
                command.type = Command::CmdType::C_POP;
            }
            command.cmd = str1;
            command.arg1 = str2;
            command.arg2 = stoi(str3);
            //cout << "push/pop:" << str1 << " " << str2 << " " << str3 << endl;
        }
        else{// 算术/逻辑运算指令
            //cout << "3.算术运算指令:" <<tmpLine<< endl;
            command.type = Command::CmdType::C_ARITHMETIC;
            command.cmd = tmpLine;
            command.arg1 = "";
            command.arg2 = -1;
        }
        break;
    }
}

Parser::Command::CmdType Parser::commandType()
{
    return command.type;
}

string Parser::cmd()
{
    return command.cmd;
}
string Parser::arg1(){
    return command.arg1;
}

int  Parser::arg2(){
    return command.arg2;
}

string Parser::RemoveSpaceAndComment(const string& str){
    return RemoveComment(RemoveSpace(str));
}

string Parser::RemoveSpace(const string& str){
    string tmpStr = str;
    auto iter = remove_if(tmpStr.begin(), tmpStr.end(), ::isspace);
    tmpStr.erase(iter, tmpStr.end());
    return tmpStr;
}

string Parser::RemoveComment(const string& str){
    return str.substr(0, str.find("//"));
}

string Parser::curCommand(){
    string str = "";
    str += command.cmd;
    if(command.arg1 != "") str += " " + command.arg1;
    if(command.arg2 != -1) str += " " + to_string(command.arg2);
    return str;
}