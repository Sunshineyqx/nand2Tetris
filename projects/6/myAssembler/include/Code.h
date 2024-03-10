#ifndef CODE_H
#define CODE_H
#include <iostream>
#include <unordered_map>
using namespace std;

class Code{
public:
    Code();
    string dest(string destH);
    string comp(string compH);
    string jump(string jumpH);
    string processA(string a);
    string processA(int a);
private:
    unordered_map<string, string> destTable;
    unordered_map<string, string> compTable;
    unordered_map<string, string> jumpTable;
};

#endif