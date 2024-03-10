#include "../include/Parser.h"
#include <algorithm>

Parser::Parser(const std::string& filename):asm_file(filename), cur_lineNum(0){
    if(!asm_file.is_open()) {
        std::cerr << "file is not open" << std::endl;
        exit(1);
    }
}

Parser::~Parser(){
    asm_file.close();
}

bool Parser::hasMoreCommands(){
    return !asm_file.eof();
}

bool Parser::advance(){
    if(!hasMoreCommands()) return false;
    std::string cur_line;
    bool found = false;
    size_t comment_pos;

    while(!found && getline(asm_file, cur_line)){
        cur_lineNum++;
        cur_line.erase(remove_if(cur_line.begin(), cur_line.end(),  ::isspace), cur_line.end());
        comment_pos = cur_line.find("//");
        if(comment_pos != std::string::npos){
            cur_line.erase(comment_pos, cur_line.length() - comment_pos);
        }
        found = !cur_line.empty();
    }
    if(found) {
        cur_instruction = cur_line;
        //std::cout << cur_line << std::endl;
        return true;
    }
    else return false;
}

std::string Parser::comp(){
    size_t equal_pos = cur_instruction.find("=");
    size_t sem_pos = cur_instruction.find(";");
    // D = C; JMP
    if(equal_pos != std::string::npos && sem_pos != std::string::npos){
        return cur_instruction.substr(equal_pos + 1,  sem_pos - equal_pos - 1);
    }
    // C; JMP
    else if(equal_pos == std::string::npos){
        return cur_instruction.substr(0, sem_pos);
    }
    // D = C
    else if(sem_pos == std::string::npos){
        return cur_instruction.substr(equal_pos + 1, cur_instruction.length() - equal_pos - 1);
    }
    else
        return ""; //语法error
}

std::string Parser::dest(){
    size_t equal_pos = cur_instruction.find("=");
    //D=C(;JMP)
    if(equal_pos != std::string::npos){
        return cur_instruction.substr(0, equal_pos);
    }
    else return ""; // 没有dest
}

std::string Parser::jump(){
    size_t sem_pos = cur_instruction.find(";");
    if(sem_pos != std::string::npos){
        return cur_instruction.substr(sem_pos + 1, cur_instruction.length() - sem_pos - 1);
    }
    else return ""; // 没有jump
}

std::string Parser::symbol(){
    size_t leftBracketPos = cur_instruction.find('(');
    size_t rightBracketPos = cur_instruction.find(')');

    if(cur_instruction[0] == '@') return cur_instruction.substr(1, cur_instruction.length() - 1);
    else if(leftBracketPos != std::string::npos and rightBracketPos != std::string::npos){
        return cur_instruction.substr(leftBracketPos + 1, rightBracketPos - leftBracketPos - 1);
    }
    else return "";
}

enum InstructionType Parser::instructionType(){

    if(cur_instruction[0] == '@') return A_INSTRUCTION;
    else if(cur_instruction[0] == '(') return L_INSTRUCTION;
    else return C_INSTRUCTION;
    
}