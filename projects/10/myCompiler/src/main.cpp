#include <iostream>
#include "../include/JackTokenizer.h"

int main(int argc, char* argv[]) {
    JackTokenizer tokenizer("./test.jack");

    while(tokenizer.hasMoreTokens()) {
        tokenizer.advance();
    }
    return 0;
}