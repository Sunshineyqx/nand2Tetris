#ifndef CODEWRITER_H
#define CODEWRITER_H

#include <iostream>
#include <fstream>
#include <map>
#include "./Parser.h"
using namespace std;

class CodeWriter{
public:
    CodeWriter(const string& filePath);
    ~CodeWriter();
    void WriteArithmetic(const string& command);
    void WritePushPop(const string& command, const string& segment, int index);
    void WriteComment(const string& str);
private:
    void segmentInit();
    string processAdd();
    string processSub();
    string processNeg();
    string processPush(const string & segment, int index);
    string processPop(const string & segment, int index);
    string processCompare(const string& command); // gt 、lt、eq
    string processLogic(const string& command); // and、or、not

    string spSub1();
    string dereferenceSpToD();
    string addDereferenceSpToD();
    string subDereferenceSpToD();
    string DtoDereferenceSp();
    string spAdd1();

private:
    ofstream outFile;
    map<string, string> _segment;
    map<string, string> _operator;
};

#endif