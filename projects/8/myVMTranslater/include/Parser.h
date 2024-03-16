#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Parser{
public:
    struct Command{
        enum CmdType{
            C_ARITHMETIC,
            C_PUSH,
            C_POP,
            C_LABEL,
            C_GOTO,
            C_IF,
            C_FUNCTION,
            C_RETURN,
            C_CALL,
            C_UNKONWN
        };
        CmdType type;
        string cmd;
        string arg1;
        int arg2;
    };

public:
    Parser(const string& filePath);
    ~Parser();
    
    bool hasMoreCommands();
    void advance();
    Command::CmdType commandType();
    string cmd();
    string arg1();
    int arg2();
    string curCommand();
private:
    string RemoveSpacesFront(const string& str);
    string RemoveAllSpaces(const string& str);
    string RemoveComment(const string& str);
    string RemoveSpacesFrontAndComment(const string& str);
    void commandClear();
private:
    ifstream inFile;
    string fileName;
    Command command;
};


#endif