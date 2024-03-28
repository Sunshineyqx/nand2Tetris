#ifndef JACKTOKENIZER_H_
#define JACKTOKENIZER_H_

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <variant>
#include <fstream>
using namespace std;

enum TokenType {KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST};

enum KeyWord { CLASS, METHOD, FUNCTION, CONSTRUCTOR, INT, BOOLEAN, CHAR, VOID, VAR, STATIC, FIELD, LET, DO, IF,
               ELSE, WHILE, RETURN, TRUE, FALSE, null, THIS  };

struct Token{
    TokenType type;
    variant<string, int> val;
};

class JackTokenizer{
public:
    JackTokenizer(const string& filePath);
    ~JackTokenizer();

    bool hasMoreTokens();
    void advance();
    Token getNextToken(); // 不会影响curToken和index
    TokenType getTokenType();

    string keyWord();
    char symbol();
    string identifier();
    int intVal();
    string stringVal();
private:
    void initSymbols();
    void initKeyWords();
    bool isIdentifier(char c);
    bool isKeyWord(string str);
    bool isSymbol(char c);
    void processIntConst();
    void processKeywordAndIdentifier();
    void processStringConst();
    void processInlineComment();
    void processBlockComment();
    void processSymbol();

private:
    ifstream inFile;
    string srcCode;
    Token curToken;
    int index;
    set<string> keyWords; 
    set<char> symbols;
};



#endif // HEADER