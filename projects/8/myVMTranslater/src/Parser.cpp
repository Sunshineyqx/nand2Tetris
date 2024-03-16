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
        string tmpLine = RemoveSpacesFrontAndComment(line);
        if(tmpLine.empty() || tmpLine.size() == 0 || tmpLine.size() == 1) continue;
        if(tmpLine.find("\r") != string::npos) { tmpLine = tmpLine.substr(0,  tmpLine.size() - 1);} //有必要么
        string str1, str2, str3;
        //cmd arg1 arg2
        if(tmpLine.find("push") != string::npos || tmpLine.find("pop") != string::npos || tmpLine.find("function") != string::npos || tmpLine.find("call")!=string::npos){
            auto index1 = tmpLine.find_first_of(" ");
            auto index2 = tmpLine.find_first_of(" ", index1 + 1);
            str1 = tmpLine.substr(0, index1);
            str2 = tmpLine.substr(index1 + 1, index2 - (index1 + 1));
            str3 = tmpLine.substr(index2 + 1);
            //cout << "1.*"<< str1 << "*"<< str2 <<  "*"<<str3 <<"*"<<endl;
            str1 = RemoveAllSpaces(str1);
            str2 = RemoveAllSpaces(str2);
            str3 = RemoveAllSpaces(str3);
            if(str1 == "push")  command.type = Command::CmdType::C_PUSH;
            else if(str1 == "pop")  command.type = Command::CmdType::C_POP;
            else if(str1 == "function") command.type = Command::CmdType::C_FUNCTION;
            else if(str1 == "call") command.type = Command::CmdType::C_CALL;

            command.cmd = str1;
            command.arg1 = str2;
            command.arg2 = stoi(str3);
        }//cmd arg1
        else if(tmpLine.find("label")!= string::npos or tmpLine.find("if-goto") != string::npos or tmpLine.find("goto") != string::npos){ //分支
            auto index1 = tmpLine.find_first_of(" ");
            str1 = tmpLine.substr(0, index1);
            str2 = tmpLine.substr(index1 + 1);
            if(str1 == "label") command.type = Command::CmdType::C_LABEL;
            else if(str1 == "if-goto") command.type = Command::CmdType::C_IF;
            else if(str1 == "goto") command.type = Command::CmdType::C_GOTO;
            str1 = RemoveAllSpaces(str1);
            str2 = RemoveAllSpaces(str2);
            command.cmd = str1;
            command.arg1 = str2;
            command.arg2 = -1;
        }
        else{//cmd =====> return 、算术指令
            tmpLine = RemoveAllSpaces(tmpLine);
            if(tmpLine == "return")   command.type = Command::CmdType::C_RETURN;
            else command.type = Command::CmdType::C_ARITHMETIC;
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

string Parser::RemoveSpacesFrontAndComment(const string& str){
    return RemoveComment(RemoveSpacesFront(str));
}

string Parser::RemoveSpacesFront(const string& str){
   //删除开头空格
    auto it = std::find_if(str.begin(), str.end(), [](char c) {
        return !std::isspace(static_cast<unsigned char>(c));
    });
        // 如果没有找到非空格字符，返回原字符串
    if (it == str.end()) {
        return str;
    }
    // 从非空格字符开始复制字符串
    return std::string(it, str.end());
}

string Parser::RemoveAllSpaces(const string &str)
{
    //删除全部空格
    string tmpStr = str;
    auto iter = remove_if(tmpStr.begin(), tmpStr.end(), ::isspace);
    tmpStr.erase(iter, tmpStr.end());
    return tmpStr;
}

string Parser::RemoveComment(const string &str)
{
    return str.substr(0, str.find("//"));
}

string Parser::curCommand(){
    string str = "";
    str += command.cmd;
    if(command.arg1 != "") str += " " + command.arg1;
    if(command.arg2 != -1) str += " " + to_string(command.arg2);
    return str;
}