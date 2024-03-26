#include <iostream>
#include "../include/JackTokenizer.h"
#include "../include/CompilationEngine.h"

int main(int argc, char* argv[]) {
    string xmlPath = "./test.xml";
    JackTokenizer tokenizer("./test.jack");
    
    CompilationEngine compilationEngine(&tokenizer, xmlPath);
    return 0;
}