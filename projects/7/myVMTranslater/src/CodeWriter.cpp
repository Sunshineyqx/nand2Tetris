#include "../include/CodeWriter.h"
static int labelCnt = 0;

CodeWriter::CodeWriter(const string &filePath): outFile(filePath)
{
    segmentInit();
}

CodeWriter::~CodeWriter()
{
    outFile.close();
}

void CodeWriter::WriteArithmetic(const string &command)
{
    string out;
    if(command == "add"){
        out = processAdd();
    }
    else if(command == "sub"){
        out = processSub();
    }
    else if(command == "neg"){
        out = processNeg();
    }
    else if(command == "eq" || command == "gt" || command == "lt"){
        out = processCompare(command);
    }
    else if(command == "and" || command == "or" || command == "not"){
        out = processLogic(command);
    }
    else{
        cerr << "WirteArithmetic(const string&): unknown command"<<endl;
        exit(1);
    }
    outFile << out << endl;
}

 void CodeWriter::WritePushPop(const string& command, const string& segment, int index){
    if(command == "push"){
        string out = processPush(segment, index);
        outFile << out << endl;
    }
    else{ //pop
        string out = processPop(segment, index);
        outFile << out << endl; 
    }
 }
 // private functions
 void CodeWriter::segmentInit(){
    _segment["local"] = "LCL";
    _segment["argument"] = "ARG";
    _segment["this"] = "THIS";
    _segment["that"] = "THAT";
    _segment["temp"] = "R5";
    _segment["static"] = "R16";
    _segment["pointer"] = "R3";

    _operator["eq"] = "JEQ";
    _operator["gt"] = "JGT";
    _operator["lt"] = "JLT";
 }

string CodeWriter::processAdd(){
    string str="";
    // 1.sp = sp -1
    str += spSub1();
    // 2. D = *sp
    str += dereferenceSpToD();
    //3. sp = sp -1
    str += spSub1();
    // 4. D = D + *sp
    str += addDereferenceSpToD();
    // 5. *sp = D
    str += DtoDereferenceSp();
    // 6. sp = sp+1
    str += spAdd1();
    
    return str;
}

string CodeWriter::processSub(){
        string str="";
    // 1.sp = sp -1
    str += spSub1();
    // 2. D = *sp
    str += dereferenceSpToD();
    //3. sp = sp -1
    str += spSub1();
    // 4. D = *sp - D   //和processAdd唯一的差别
    str += subDereferenceSpToD();
    // 5. *sp = D
    str += DtoDereferenceSp();
    // 6. sp = sp+1
    str += spAdd1();
    
    return str;
}

string CodeWriter::processNeg(){
    string str = "";
    //1. sp--
    str += spSub1();
    //2. D = *sp
    str += dereferenceSpToD();
    //3. D = -D
    str += "D = -D\n";
    //4. *sp = D
    str += DtoDereferenceSp();
    //5. sp++
    str += spAdd1();

    return str;
}

string CodeWriter::processCompare(const string& command){
    string cmd = _operator[command];
    string str = "";
    // 1. sp--
    str += spSub1();
    // 2. D = *sp
    str += dereferenceSpToD();
    // 3. sp--
    str += spSub1();
    // 4. D =  *sp(M) - D
    str += "@SP\n" + string("") + "A = M\n" + "D = M - D\n";
    // 5. @TrueLabel + i   D; cmd
    str += "@TrueLabel" + string("") + to_string(labelCnt) + "\n";
    str += "D;" + cmd + "\n";
    //6. *sp = 0
    str += "@SP\n" + string() + "A = M\n" + "M = 0\n";
    //7. @EndLabel  + i   0; JMP 
    str += "@EndLabel" + to_string(labelCnt) + "\n";
    str += "0;JMP\n";
    //7. (TrueLabel + i)     *sp = -1
    str += "(TrueLabel" + to_string(labelCnt) + ")\n";
    str += "@SP\n" + string() + "A = M\n" + "M = -1\n";
    //8. (EndLabel + i)  sp++
    str += "(EndLabel" + to_string(labelCnt) + ")\n";
    str += spAdd1();

    labelCnt++;
    return str;
}

string CodeWriter::processLogic(const string & command){
    string str = "";
    if(command == "and" || command == "or"){
        //1. sp--
        str += spSub1();
        //2. D = *sp
        str += dereferenceSpToD();
        //3. sp--
        str += spSub1();
        //4. D = D & *sp(M) or D = D | *sp(M)
        str += "@SP\n" + string() + "A = M\n" + ((command == "and") ? "D = D & M\n" : "D = D | M\n");
       //5. *sp = D
        str += DtoDereferenceSp();
       //6. sp++
       str += spAdd1();
        return str;
    }
    else if(command == "not"){
        string str = "";
        //1. sp--
        str += spSub1();
        //2. D = *sp
        str += dereferenceSpToD();
        //3. D = !D
        str += "D = !D\n";
       //4. *sp = D
        str += DtoDereferenceSp();
       //5. sp++
       str += spAdd1();
        return str;
    }
    else{
        cerr <<"processLogic(): Unknown command" <<endl;
        exit(1);
    }
}

string CodeWriter::processPush(const string & segment, int index){
    string str = "";
    if(segment == "local" or segment == "argument" or segment == "this" or segment == "that"){
        // 1. baseAddr = *segment====>D
        str += "@" + _segment[segment] + "\n" + "D = M\n";
        //2. addr = baseAddr + index====>D
        str += "@" + to_string(index) + "\n" + "D = D + A\n";
        //3. D = *addr
        str += "A = D\n" + string("") + "D = M\n";
        // 4. *sp = D
        str += "@SP\n" + string("") +"A = M\n"+ "M = D\n";
        // 5. sp++
        str += spAdd1();

        return str;
    }
    else if(segment == "constant"){
        // 1. D = index
        str += "@" + to_string(index) + "\n" + "D = A\n";
        // 2. *sp = D
        str += DtoDereferenceSp();
        //3.   sp++
        str += spAdd1();
        return str;
    }
    else if(segment == "pointer"){
        // 1. D = THIS/THAT
        str += string("@") + ((index == 0) ? "R3\n" : "R4\n") + "D = M\n";
        // 2. *sp = D
        str += "@SP\n" + string("") +"A = M\n"+ "M = D\n";
        // 3. sp++
        str += spAdd1();

        return str;
    }
    else if(segment == "temp" or segment == "static"){
        //1. addr = temp/static + index ====> D
        str += "@" + _segment[segment] + "\n" + "D = A\n" + "@" + to_string(index)+"\n" + "D = D + A\n";
        //2. *sp = *addr
        str += "A = D\n" + string("") +"D = M\n" + "@SP\n" + "A = M\n" + "M = D\n";
        //3. sp++
        str += spAdd1();
        return str;
    }
    else{
        return "";
    }
}

string CodeWriter::processPop(const string & segment, int index){
        string str = "";
        if(segment == "local" or segment == "argument" or segment == "this" or segment == "that"){
        // 1. baseAddr = *segment ====> D
        str += "@" + _segment[segment] + "\n" + "D = M\n";
        //2. addr = baseAddr + index ====> D
        str += "@" + to_string(index) + "\n" + "D = D + A\n";
        //3. R13 = addr（通用寄存器）
        str += "@R13\n" + string("") + "M = D\n";
        // 4. sp--
        str += spSub1();
        // 5. D = *sp
        str += dereferenceSpToD(); 
        //6. *R13 = D
        str += "@R13\n" + string("") +"A = M\n"+ "M = D\n";

        return str;
    }
        else if(segment == "pointer"){
        //1. sp--
        str += spSub1();
        //2. D = *sp
        str += dereferenceSpToD();
        //3. THIS/THAT = D
        str += string("@") + ((index == 0) ? "R3\n" : "R4\n") +  "M = D\n";
        return str;
    }
    else if(segment == "temp" or segment == "static"){
        // 1. addr = temp/static + index ===> D
        str += "@" + _segment[segment] + "\n" + "D = A\n" + "@" + to_string(index)+"\n" + "D = D + A\n";
        //2. sp--
        str += spSub1();
        //3. addr存储到R13(通用寄存器)
        str += "@R13\n" + string("") + "M = D\n";
        //4. *R13 = *sp
        str += "@SP\n" + string("") + "A = M\n" + "D = M\n" + "@R13\n" + "A = M\n" + "M = D\n";
        return str;
    }
    else{
        return "";
    }
}

string CodeWriter::spSub1(){
    return "@SP\nM = M - 1\n";
}

string CodeWriter::dereferenceSpToD(){
    return "@SP\nA = M\nD = M\n";
}
string CodeWriter::addDereferenceSpToD(){
    return "@SP\nA = M\nD = D + M\n";
}
string CodeWriter::subDereferenceSpToD(){
    return "@SP\nA = M\nD = M - D\n";
}
string CodeWriter::DtoDereferenceSp(){
    return "@SP\nA = M\nM = D\n";
}

string CodeWriter::spAdd1(){
    return "@SP\nM = M + 1\n";
}

void CodeWriter::WriteComment(const string& str){
    outFile << "//" << str << endl;
}