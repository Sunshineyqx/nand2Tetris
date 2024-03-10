#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <unordered_map>
using namespace std;
class SymbolTable{
public:
    SymbolTable();
    ~SymbolTable() = default;

    void addEntry(string name, int address);
    bool isContained(string name);
    int getAddress(string name);

private:
    unordered_map<string, int> symbolTable;
};

#endif