#include "../include/JackTokenizer.h"
using namespace std;
#include <sstream>
#include <cctype>

JackTokenizer::JackTokenizer(const std::string& filePath): inFile(filePath), index(0), testToken("./debug/testToken.txt"){
    if(!inFile.is_open()){
        cerr << "JackTokenizer::JackTokenizer(const std::string& filePath): 打开文件失败..." << endl;
    }

    ostringstream tmp;
    tmp << inFile.rdbuf();
    srcCode = tmp.str();
    //cout << srcCode << endl;
    initSymbols();
    initKeyWords();
}

JackTokenizer::~JackTokenizer()
{
    if(inFile.is_open()){
        inFile.close();
    }
}

bool JackTokenizer::hasMoreTokens(){
    if(!inFile.is_open()){
        cerr << "输入文件未打开" <<endl; 
        return false;
    }
    return index < srcCode.size();
}

void JackTokenizer::advance(){
    //token parse
    while(1){
        if(index >= srcCode.size()){
            break;
        }

        char nowChar = srcCode[index];
        if(nowChar >= '0' && nowChar <= '9'){         // INT_CONST (标识符不会以数字开头)
            processIntConst();
            break;
        }
        else if((nowChar >= 'a' && nowChar <= 'z') || (nowChar >= 'A' && nowChar <= 'Z') || (nowChar == '_')){ //keyword or identifier
            processKeywordAndIdentifier();
            break;
        }
        else if(nowChar == '"'){    // STRING_CONST
            processStringConst();
            break;
        }
        else if(nowChar == '\r' || nowChar == '\n' || nowChar == ' ' || nowChar == '\0' || nowChar == '\t'){ //空白和换行
            index++;
            continue;
        }
        else if(nowChar == '/') //注释 或者 symbol:/
        {
            if(srcCode[index + 1] == '/'){ //单行注释
                processInlineComment();
                continue;
            }
            else if(srcCode[index +1] == '*'){ //多行注释
                processBlockComment();
                continue;
            }
            else{ //symbol:/
                processSymbol();
                break;
            }
        }
        else if(isSymbol(nowChar)){ //other symbols
            processSymbol();
            break;
        }
        else{ //unkown char...
            cerr << "advance(): unknown char: " << nowChar << endl;
            exit(1);
        }
        
    }
    
}

TokenType JackTokenizer::getTokenType(){
    return curToken.type;
}

string JackTokenizer::keyWord(){
    return get<string>(curToken.val);
}

char JackTokenizer::symbol(){
    return get<string>(curToken.val)[0];
}

string JackTokenizer::identifier(){
    return get<string>(curToken.val);
}

int JackTokenizer::intVal(){
    return get<int>(curToken.val);
}

string JackTokenizer::stringVal(){
    return get<string>(curToken.val);
}

//gets the next token!
Token JackTokenizer::getNextToken(){
    int lastIndex = index;
    Token lastToken = curToken;
    advance();
    Token nextToken = curToken;
    index = lastIndex;
    curToken = lastToken;
    return nextToken;
}

//helper function
void JackTokenizer::initSymbols(){
    string specialCharsStr = "{}()[].,;+-*&|<>=~";
    symbols.insert(specialCharsStr.begin(), specialCharsStr.end());
    /*
    for(char c : symbols){
        cout << c << " ";
    }
    cout << endl;
    */
}

void JackTokenizer::initKeyWords(){
    keyWords.insert("class");
    keyWords.insert("method");
    keyWords.insert("function");
    keyWords.insert("constructor");
    keyWords.insert("int");
    keyWords.insert("boolean");
    keyWords.insert("char");
    keyWords.insert("void");
    keyWords.insert("var");
    keyWords.insert("static");
    keyWords.insert("field");
    keyWords.insert("let");
    keyWords.insert("do");
    keyWords.insert("if");
    keyWords.insert("else");
    keyWords.insert("while");
    keyWords.insert("return");
    keyWords.insert("true");
    keyWords.insert("false");
    keyWords.insert("null");
    keyWords.insert("this");
    /*
    for(string s : keyWords){
        cout << s << " ";
    }
    */
}

bool JackTokenizer::isIdentifier(char c){
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') || (c == '_'));
}

bool JackTokenizer::isKeyWord(string str){
    return keyWords.find(str) != keyWords.end();
}

bool JackTokenizer::isSymbol(char c){
    return symbols.find(c) != symbols.end();
}

void JackTokenizer::processIntConst(){
    auto firstIndex = index;
    while(srcCode[index] >= '0' && srcCode[index] <= '9'){
        index++;
    }
    curToken.type = INT_CONST;
    curToken.val = stoi(srcCode.substr(firstIndex, index - firstIndex));
    //testToken << intVal() << endl;
}

void JackTokenizer::processKeywordAndIdentifier(){
    auto fastIndex = index + 1;
    while(isIdentifier(srcCode[fastIndex])){ 
        fastIndex++; 
    }
    auto str = srcCode.substr(index, fastIndex-index);
    if(isKeyWord(str)){
        curToken.type = KEYWORD;
        curToken.val = str;
        //testToken << keyWord() << endl;
    }
    else{
        curToken.type = IDENTIFIER;
        curToken.val = str;
        //testToken << identifier() <<endl;

    }
    index = fastIndex;
}

void JackTokenizer::processStringConst(){
    auto firstIndex = index + 1;
    auto lastIndex = srcCode.find('"', firstIndex);

    curToken.type = STRING_CONST;
    curToken.val = srcCode.substr(firstIndex, lastIndex-firstIndex);
    index = lastIndex + 1;
    //testToken <<stringVal() <<endl;
}

void JackTokenizer::processInlineComment(){
    string breakLineSymbol = "\n"; // break line...
    auto lastIndex = srcCode.find(breakLineSymbol, index + 2);
    if(lastIndex != string::npos){
        index = lastIndex + 1;
    }
    else{
        cerr << "processInlineComment() error: not found \n" <<endl;
        exit(1);
    }
}

void JackTokenizer::processBlockComment(){
    auto lastIndex = srcCode.find("*/", index + 2);
    index = lastIndex + 2;
}

void JackTokenizer::processSymbol(){
    curToken.type = SYMBOL;
    curToken.val = string(1, srcCode[index]);
    ++index;
    //testToken << symbol() << endl;
}



