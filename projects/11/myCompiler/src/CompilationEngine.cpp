#include "../include/CompilationEngine.h"
#include <assert.h>
#include <sstream>
namespace CEHelper{
    symboltable::Kind keyWord2Kind(string key){
        if(key == "static") return symboltable::Kind::STATIC;
        else if(key == "field") return symboltable::Kind::FIELD;
        else if(key == "var") return symboltable::Kind::VAR;
        else return symboltable::Kind::NONE;
    }

    vm::Segment kind2Segment(symboltable::Kind kind)
	{
		switch(kind)
		{
			case symboltable::STATIC:
				return vm::STATIC;
			case symboltable::FIELD:
				return vm::THIS;
			case symboltable::ARG:
				return vm::ARG;
			case symboltable::VAR:
				return vm::LOCAL;
            default:
                return vm::UNKNOWN;
		}
	}
}

CompilationEngine::CompilationEngine(JackTokenizer* tokenizer, VMWriter * VM, SymbolTable * ST): _JT(tokenizer), _VM(VM), _ST(ST),
    _className(), _subroutineType(), _returnType(), _currentFunctionName(), _argNums(0), _labelNums(0){
    compileClass(); //entry point
}

CompilationEngine::~CompilationEngine()
{
    _VM->close();
    cout << "Compilation Complete!" << endl;
}

// Compiles a complete class
void CompilationEngine::compileClass(){
    _JT->advance();
    assert(_JT->keyWord() == "class");

    _JT->advance();
    assert(_JT->getTokenType() == IDENTIFIER);
    _className = _JT->identifier();

    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '{');

    _JT->advance();
    while((_JT->getTokenType() == KEYWORD) && (_JT->keyWord() == "static" || _JT->keyWord() == "field" || _JT->keyWord() == "constructor" 
            || _JT->keyWord() == "function" || _JT->keyWord() == "method")){
        if(_JT->keyWord() == "static" || _JT->keyWord() == "field"){
            compileClassVarDec();
        }
        else if(_JT->keyWord() == "constructor" || _JT->keyWord() == "function" || _JT->keyWord() == "method"){
            compileSubroutine();
        }
        else{
            cerr << "compileClass(): 源码中存在错误的关键字!..." << endl;
            exit(1);
        }
        _JT->advance();
    }
    //cout << _JT->keyWord() << endl;
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '}');
}

void CompilationEngine::compileClassVarDec(){
    string name, type;
    symboltable::Kind kind;
    kind = CEHelper::keyWord2Kind(_JT->keyWord());

    _JT->advance();
    if(_JT->getTokenType() == KEYWORD){
        assert(_JT->keyWord() == "int" || _JT->keyWord() == "char" || _JT->keyWord() == "boolean");
        type = _JT->keyWord();
    }
    else if(_JT->getTokenType() == IDENTIFIER){
        type = _JT->identifier();
    }
    else{
        cerr << "compileClassVarDec(): syntax error..." << endl;
        exit(1);
    }

    _JT->advance();
    while(!(_JT->getTokenType() == SYMBOL && (_JT->symbol() == ';'))){
        if(_JT->getTokenType() == IDENTIFIER){
            name = _JT->identifier();
            _ST->define(name, type, kind);
        }
        else if(_JT->getTokenType() == SYMBOL && _JT->symbol() == ','){
        }
        else{
            cerr << "compileClassVarDec(): 变量声明不正确..."<<endl;
            exit(1);
        }
        _JT->advance();
    }
    assert(_JT->getTokenType() == SYMBOL && (_JT->symbol() == ';'));
}

void CompilationEngine::compileSubroutine(){
    _ST->startSubroutine(); // 每次开始编译新例程开创一个新的子例程符号表
    _subroutineType = _JT->keyWord();
    if(_subroutineType == "method"){
        _ST->define("this", _className, symboltable::ARG);
    }

    _JT->advance();
    if(_JT->getTokenType() == KEYWORD){
        assert(_JT->keyWord() == "int" || _JT->keyWord() == "char" || _JT->keyWord() == "void" || _JT->keyWord() == "boolean");
        _returnType = _JT->keyWord();
    }
    else if(_JT->getTokenType() == IDENTIFIER){
        _returnType = _JT->identifier();
    }
    else{
        cerr << "compileSubroutine(): syntax error..." << endl;
        exit(1);
    }

    _JT->advance();
    assert(_JT->getTokenType() == IDENTIFIER);
    _currentFunctionName = _className + "." + _JT->identifier();

    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '(');

    _JT->advance();
    compileParameterList();

    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');

    _JT->advance();
    compileSubroutineBody();

}

void CompilationEngine::compileParameterList(){
    string name,type;
    symboltable::Kind kind = symboltable::Kind::ARG;
    int flags = 0; //0:代表当前token是变量类型 1:代表当前token是变量名

    while(!(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')')){
        if(_JT->getTokenType() == KEYWORD){
            if(flags == 0){
                type = _JT->keyWord();
                flags = 1;        
            }
        }
        else if(_JT->getTokenType() == IDENTIFIER){
            if(flags == 1){
                name = _JT->identifier();
                _ST->define(name, type, kind);
                flags = 0;
            }
            else if(flags == 0){
                type = _JT->identifier();
                flags = 1;
            }
        }
        else if(_JT->getTokenType() == SYMBOL && _JT->symbol() == ','){
            flags = 0;
        }
        else{
            cerr << "compileParameterList(): 参数列表存在错误信息..." << endl;
            exit(1);
        }
        _JT->advance();
    }
}

void CompilationEngine::compileSubroutineBody(){
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '{');

    _JT->advance();
    while(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "var"){
        compileVarDec();
    }

    int nLocals = _ST->varCount(symboltable::VAR);
    _VM->writeFunction(_currentFunctionName, nLocals);
    if(_subroutineType == "constructor"){
        _VM->writePush(vm::Segment::CONST, _ST->varCount(symboltable::FIELD));
        _VM->writeCall("Memory.alloc", 1);
        _VM->writePop(vm::Segment::POINTER, 0);
    }
    else if(_subroutineType == "method"){
        _VM->writePush(vm::Segment::ARG, 0);
        _VM->writePop(vm::Segment::POINTER, 0);
    }
    else{
        //function: do nothing
    }

    if(_JT->getTokenType() == KEYWORD && (_JT->keyWord() == "let" || _JT->keyWord() == "do" || _JT->keyWord() == "if"
            || _JT->keyWord() == "while" || _JT->keyWord() == "return")){
        compileStatements();
    }
    else if(_JT->getTokenType() == KEYWORD && (_JT->keyWord() == "else")){
        cerr << "compileSubroutineBody(): 存在语法错误, else不能单独出现..."<<endl;
        exit(1);
    }

}

void CompilationEngine::compileVarDec(){
    string name,type;
    symboltable::Kind kind = symboltable::Kind::VAR;

    assert(_JT->getTokenType() == KEYWORD && (_JT->keyWord() == "var"));

    _JT->advance();
    if(_JT->getTokenType() == IDENTIFIER){
        type = _JT->identifier();
    }
    else if(_JT->getTokenType() == KEYWORD && (_JT->keyWord() == "int" ||_JT->keyWord() == "boolean" || _JT->keyWord() == "char")){
        type = _JT->keyWord();
    }

    _JT->advance();
    assert(_JT->getTokenType() == IDENTIFIER);
    name = _JT->identifier();
    _ST->define(name, type, symboltable::VAR);

    _JT->advance();
    while(_JT->getTokenType() == SYMBOL && _JT->symbol() == ','){ // a,b,c...;
        _JT->advance();
        assert(_JT->getTokenType() == IDENTIFIER);
        name = _JT->identifier();
        _ST->define(name, type, symboltable::VAR);
        _JT->advance();
    }
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ';');

    _JT->advance();
}

void CompilationEngine::compileStatements(){
    while(_JT->getTokenType() == KEYWORD && (_JT->keyWord() == "let" || _JT->keyWord() == "if" || _JT->keyWord() == "else" || _JT->keyWord() == "while" || _JT->keyWord() == "do" || _JT->keyWord() == "return")){
        if(_JT->keyWord() == "let"){
            compileLet();
        }
        else if(_JT->keyWord() == "if"){
            compileIf();
        }
        else if(_JT->keyWord() == "else"){
            cerr << "compileStatements(): 语法错误,else不能单独出现..."<<endl;
            exit(1);
        }
        else if(_JT->keyWord() == "while"){
            compileWhile();
        }
        else if(_JT->keyWord() == "do"){
            compileDo();
            //cout << _JT->getTokenType() << " " << _JT->symbol() << endl;
        }
        else if(_JT->keyWord() == "return"){
            compileReturn();
        }
        else{
            cerr << "compileStatements(): 未知的keyword..."<<endl;
            exit(1);
        }
    }

}

void CompilationEngine::compileLet(){
    assert(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "let");

    _JT->advance();
    assert(_JT->getTokenType() == IDENTIFIER);
    string lhsVar = _JT->identifier();
    int isArray = 0;

    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL);
    if(_JT->symbol() == '='){  // a = expression;
    }
    else if(_JT->symbol() == '['){ //a[expression] = expression;
        _JT->advance();
        compileExpression();
        _VM->writePush(CEHelper::kind2Segment(_ST->kindOf(lhsVar)), _ST->indexOf(lhsVar));
        _VM->writeArithmetic(vm::Command::ADD);
        isArray = 1;
        assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ']');

        _JT->advance();
        assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '=');
    }
    else{
        cerr << "compileLet(): syntax error...<<endl";
        exit(1);
    }

    _JT->advance();
    compileExpression();

    if(isArray == 1) {
        _VM->writePop(vm::Segment::TEMP, 0);
        _VM->writePop(vm::Segment::POINTER, 1);
        _VM->writePush(vm::Segment::TEMP, 0);
        _VM->writePop(vm::Segment::THAT, 0);
    }
    else if(isArray == 0) {
        _VM->writePop(CEHelper::kind2Segment(_ST->kindOf(lhsVar)), _ST->indexOf(lhsVar));
    }

    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ';');

    _JT->advance();
}

void CompilationEngine::compileIf(){
    stringstream labelFalse, labelContinue;
    labelFalse << _VM->getFileName() <<".IFFALSE"  << _labelNums;
    labelContinue << _VM->getFileName() << ".CONTINUE" <<  _labelNums;
    _labelNums++;

    assert(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "if");

    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '(');

    _JT->advance();
    compileExpression();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
    _VM->writeArithmetic(vm::Command::NOT);
    _VM->writeIf(labelFalse.str());

    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '{');

    _JT->advance();
    compileStatements();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '}');
    _VM->writeGoto(labelContinue.str());

    _JT->advance();
    if(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "else"){ //else是可选的
        _JT->advance();
        assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '{');
        _VM->writeLabel(labelFalse.str());

        _JT->advance();
        compileStatements();
        assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '}');

        _JT->advance();
    }
    else{ //没有else
        _VM->writeLabel(labelFalse.str());
    }
    _VM->writeLabel(labelContinue.str());
}

void CompilationEngine::compileWhile(){
    stringstream labelTrue, labelFalse;
    labelTrue << _VM->getFileName() << ".WHILETRUE" << _labelNums;
    labelFalse << _VM->getFileName() <<".WHILEFALSE" << _labelNums;
    _labelNums++;

    assert(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "while");

    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '(');
    _VM->writeLabel(labelTrue.str());
    _JT->advance();
    compileExpression();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
    _VM->writeArithmetic(vm::Command::NOT);

    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '{');
    _VM->writeIf(labelFalse.str());
    _JT->advance();
    compileStatements();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '}');
    _VM->writeGoto(labelTrue.str());
    _VM->writeLabel(labelFalse.str());
    _JT->advance();
}

void CompilationEngine::compileDo(){
    assert(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "do");

    _JT->advance();
    assert(_JT->getTokenType() == IDENTIFIER);
    string name = _JT->identifier();// varname or classname or subroutine name

    _JT->advance();
    if(_JT->getTokenType() == SYMBOL) {
        if(_JT->symbol() == '('){ //name: subroutine name(method)
            _VM->writePush(vm::Segment::POINTER, 0);
            _JT->advance();
            compileExpressionList();

            assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
            if(_argNums > 0){
                _VM->writeCall(_className+"."+name, _argNums + 1);
            }
            else{
                _VM->writeCall(_className+"."+name, 1);
            }
            _argNums = 0;
        }
        else if(_JT->symbol() == '.'){

            _JT->advance();
            assert(_JT->getTokenType() == IDENTIFIER);
            string subroutineName = _JT->identifier();
            if(_ST->kindOf(name) != symboltable::Kind::NONE){ // varname
                _VM->writePush(CEHelper::kind2Segment(_ST->kindOf(name)), _ST->indexOf(name)); // push argument 0: var's address
                _JT->advance();
                assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '(');

                _JT->advance();
                compileExpressionList();
                assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
                _VM->writeCall(_ST->typeOf(name)+"."+subroutineName, _argNums + 1);
            }
            else{   // class name
                _JT->advance();
                assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '(');

                _JT->advance();
                compileExpressionList();

                assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
                _VM->writeCall(name + "." + subroutineName, _argNums);
            }
            _argNums = 0;

        }
        else{
            cerr << "compileDo: subroutineCall语法错误...错误的符号." << endl;
            exit(1);
        }
    }
    else{
        cerr << "compileDo: subroutineCall语法错误...类型错误"<<endl;
        exit(1);
    }
    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ';');
    _VM->writePop(vm::TEMP,0);

    _JT->advance();
}

void CompilationEngine::compileReturn(){
    assert(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "return");

    _JT->advance();
    if(_JT->getTokenType() == SYMBOL && _JT->symbol() == ';'){
        if(_returnType == "void"){
            _VM->writePush(vm::Segment::CONST, 0);
        }
        else{
            cerr << "compileReturn(): 语法错误,返回类型不为void,但是缺乏返回值..." <<endl;
            exit(1);
        }
    }
    else{
        compileExpression();
    }
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ';');
    _VM->writeReturn();
    _JT->advance();
}

void CompilationEngine::compileExpression(){
    compileTerm();

    _JT->advance();
    while(_JT->getTokenType() == SYMBOL){
        if(_JT->symbol() == ';' || _JT->symbol() == ')' || _JT->symbol() == ','||_JT->symbol() == ']'){ //end of expression...maybe more!!!
            break;
        }
        else{ //other (op term)*
            char op = _JT->symbol();
            _JT->advance();
            compileTerm();
            _JT->advance();
            if(op == '+'){
                _VM->writeArithmetic(vm::ADD);
            }
            else if(op == '-'){
                _VM->writeArithmetic(vm::SUB);
            }
            else if(op == '*'){
                _VM->writeCall("Math.multiply", 2);
            }
            else if(op == '/'){
                _VM->writeCall("Math.divide", 2);
            }
            else if(op == '>'){
                _VM->writeArithmetic(vm::Command::GT);
            }
            else if(op == '<'){
                _VM->writeArithmetic(vm::Command::LT);
            }
            else if(op == '&'){
                _VM->writeArithmetic(vm::AND);
            }
            else if(op == '|'){
                _VM->writeArithmetic(vm::OR);
            }
            else if(op == '='){
                _VM->writeArithmetic(vm::EQ);
            }
            else{
                cerr << "compileExpression(): unknown symbol " << _JT->symbol() << endl;
                exit(1);
            }

        }
    }

}

void CompilationEngine::compileTerm(){

    if(_JT->getTokenType() == INT_CONST){
        _VM->writePush(vm::Segment::CONST, _JT->intVal());
    }
    else if(_JT->getTokenType() == STRING_CONST){
        string str = _JT->stringVal();
        int length = str.length();
        _VM->writePush(vm::Segment::CONST, length);
        _VM->writeCall("String.new", 1);
        for(int i = 0; i < length; i++){
            _VM->writePush(vm::Segment::CONST, (int)str[i]);
            _VM->writeCall("String.appendChar", 2);
        }
    }
    else if(_JT->getTokenType() == KEYWORD){ //true, false, null, this
        if(_JT->keyWord() == "true"){ //true: -1
            _VM->writePush(vm::Segment::CONST, 0);
            _VM->writeArithmetic(vm::Command::NOT);
        }
        else if(_JT->keyWord() == "false"){ //false: 0
            _VM->writePush(vm::CONST,0);
        }
        else if(_JT->keyWord() == "null"){
            _VM->writePush(vm::CONST,0);
        }
        else if(_JT->keyWord() == "this"){
            _VM->writePush(vm::Segment::POINTER, 0);
        }
        else{
            cerr << "compileTerm(): keyword unknown...:"<< _JT->keyWord() << endl;
            exit(1);
        }
    }
    else if(_JT->getTokenType() == IDENTIFIER){
        string id = _JT->identifier();
        Token nextToken = _JT->getNextToken();
        char nextChar = get<string>(nextToken.val)[0];
        if(nextChar == '('){ //bar(expressionList)
            _JT->advance();
            _VM->writePush(vm::Segment::POINTER, 0); //method, so push this
            _JT->advance();
            compileExpressionList();
            assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
            if(_argNums > 0){
                _VM->writeCall(_className+"."+id, _argNums + 1);
            }
            else{
                _VM->writeCall(_className+"."+id, _argNums + 1);
            }
            _argNums = 0;
        }
        else if(nextChar == '.'){ //foo.bar(expressionList) or FOO.bar(expressionList)
            _JT->advance();

            _JT->advance();
            assert(_JT->getTokenType() == IDENTIFIER);
            string subroutineName = _JT->identifier();
            if(_ST->kindOf(id) != symboltable::Kind::NONE){ //id是varname而不是类名
                _JT->advance();
                assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '(');
                _VM->writePush(CEHelper::kind2Segment(_ST->kindOf(id)), _ST->indexOf(id));
                _JT->advance();
                compileExpressionList();

                assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
                _VM->writeCall(_ST->typeOf(id)+"."+subroutineName, _argNums+1);
            }
            else{ //id是类名
                _JT->advance();
                assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '(');

                _JT->advance();
                compileExpressionList();

                assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
                _VM->writeCall(id+"."+subroutineName, _argNums);
            }
            _argNums = 0;
        }
        else if(nextChar == '['){ //foo[expression]
            _JT->advance();
            
            _JT->advance();
            compileExpression();
            _VM->writePush(CEHelper::kind2Segment(_ST->kindOf(id)), _ST->indexOf(id));
            _VM->writeArithmetic(vm::Command::ADD);

            assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ']');
            _VM->writePop(vm::Segment::POINTER, 1);
            _VM->writePush(vm::Segment::THAT, 0);
        }
        else{ 
            _VM->writePush(CEHelper::kind2Segment(_ST->kindOf(id)), _ST->indexOf(id));
        }
    }
    else{ //一些符号开头的term
        if(_JT->symbol() == '('){ //  (expression)
            
            _JT->advance();
            compileExpression();

            assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
        }
        else if(_JT->symbol() == '-' or _JT->symbol() == '~'){ //unary op:- ~
            char uop = _JT->symbol();
            _JT->advance();
            compileTerm();
            if(uop == '-'){
                _VM->writeArithmetic(vm::Command::NEG);
            }
            else if(uop == '~'){
                _VM->writeArithmetic(vm::Command::NOT);    
            }
        }
        else{
            cerr << "compileTerm(): 错误的keyWord: " << _JT->keyWord() << endl;
            exit(1);
        }
    }
}

void CompilationEngine::compileExpressionList(){
    if(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')'){
        return;
    }
    _argNums++;
    compileExpression();
    while(!(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')')){
        _argNums++;
        _JT->advance();
        compileExpression();
    }

}


