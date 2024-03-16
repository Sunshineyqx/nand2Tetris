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
    void setFileName(const string& name);
    void WriteArithmetic(const string& command);
    void WritePushPop(const string& command, const string& segment, int index);
    void WriteComment(const string& str);
    void WriteLabel(const string& label);
    void WriteIf(const string& label);
    void WriteGoto(const string& label);
    void WriteFunction(const string& func, int localNums);
    void WriteReturn();
    void WriteCall(const string& func, int argNums);
private:
    void segmentInit();
    void vmInit();
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
    string pushConstantVal(int val);

private:
    ofstream outFile;
    string fileName;
    map<string, string> _segment;
    map<string, string> _operator;
};

#endif