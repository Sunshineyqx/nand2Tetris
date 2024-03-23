#include "../include/CompilationEngine.h"
#include <assert.h>

CompilationEngine::CompilationEngine(JackTokenizer* tokenizer, const string& outFilePath): _JT(tokenizer), outFile(outFilePath){
    if(!outFile.is_open()) {
        cerr << "CompilationEngine constructor(): 输出文件打开失败..." <<endl;
        exit(1);
    }
    compileClass(); //entry point
}

CompilationEngine::~CompilationEngine()
{
	if(outFile.is_open())
		outFile.close();
}

// Compiles a complete class
void CompilationEngine::compileClass(){
    outFile << "<class>" << endl;

    _JT->advance();
    assert(_JT->keyWord() == "class");
    outFile << "<keyword> " << "class" << " </keyword>" << endl;

    _JT->advance();
    assert(_JT->getTokenType() == IDENTIFIER);
    outFile << "<identifier> "<< _JT->identifier() << " </identifier>" << endl;

    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '{');
    outFile << "<symbol> { </symbol>" <<endl;

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
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '}');
    outFile << "<symbol> } </symbol>" << endl;
    outFile << "</class>" << endl;
}

void CompilationEngine::compileClassVarDec(){
    outFile << "<classVarDec>" << endl;
    outFile << "<keyword> " << _JT->keyWord() << " </keyword>" << endl;

    _JT->advance();
    assert(_JT->getTokenType() == KEYWORD && (_JT->keyWord() == "int" || _JT->keyWord() == "char" || _JT->keyWord() == "boolean"));
    outFile << "<keyword> " << _JT->keyWord() << " </keyword>" << endl;

    _JT->advance();
    while(!(_JT->getTokenType() == SYMBOL && (_JT->symbol() == ';'))){
        if(_JT->getTokenType() == IDENTIFIER){
            outFile << "<identifier> " << _JT->identifier() << " </identifier>" << endl;
        }
        else if(_JT->getTokenType() == SYMBOL && _JT->symbol() == ','){
            outFile << "<symbol> " << _JT->symbol() << " </symbol>" << endl;
        }
        else{
            cerr << "compileClassVarDec(): 变量声明不正确..."<<endl;
            exit(1);
        }
        _JT->advance();
    }
    assert(_JT->getTokenType() == SYMBOL && (_JT->symbol() == ';'));
    outFile << "<symbol> ; </symbol>" << endl;
    outFile << "</classVarDec>" << endl;
}

void CompilationEngine::compileSubroutine(){
    outFile << "<subroutineDec>" << endl;
    outFile << "<keyword> " << _JT->keyWord() << " </keyword>"  << endl;

    _JT->advance();
    assert(_JT->getTokenType() == KEYWORD && (_JT->keyWord() == "int" || _JT->keyWord() == "char" || _JT->keyWord() == "void" || _JT->keyWord() == "boolean"));
    outFile << "<keyword> " << _JT->keyWord() << " </keyword>" << endl;

    _JT->advance();
    assert(_JT->getTokenType() == IDENTIFIER);
    outFile << "<identifier> " << _JT->identifier() << " </identifier>" << endl;

    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '(');
    outFile << "<symbol> " << _JT->symbol() << " </symbol>" << endl;

    _JT->advance();
    compileParameterList();

    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
    outFile << "<symbol> ) </symbol>" << endl;

    _JT->advance();
    compileSubroutineBody();

    outFile << "</subroutineDec>" << endl;
}

void CompilationEngine::compileParameterList(){
    outFile << "<parameterList>" << endl;
    
    while(!(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')')){
        if(_JT->getTokenType() == KEYWORD){
            outFile << "<keyword> " << _JT->keyWord() << " </keyword>" << endl;
        }
        else if(_JT->getTokenType() == IDENTIFIER){
            outFile << "<identifier> " << _JT->identifier() << " </identifier>" << endl;
        }
        else if(_JT->getTokenType() == SYMBOL && _JT->symbol() == ','){
            outFile << "<symbol> " << _JT->symbol() << " </symbol>" << endl;
        }
        else{
            cerr << "compileParameterList(): 参数列表存在错误信息..." << endl;
            exit(1);
        }
        _JT->advance();
    }
    outFile << "</parameterList>" << endl;
}

void CompilationEngine::compileSubroutineBody(){
    outFile << "<subroutineBody>" <<endl;
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '{');
    outFile << "<symbol> { </symbol>" << endl;

    _JT->advance();
    while(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "var"){
        compileVarDec();
    }

    if(_JT->getTokenType() == KEYWORD && (_JT->keyWord() == "let" || _JT->keyWord() == "do" || _JT->keyWord() == "if"
            || _JT->keyWord() == "while" || _JT->keyWord() == "return")){
        compileStatements();
    }
    else if(_JT->getTokenType() == KEYWORD && (_JT->keyWord() == "else")){
        cerr << "compileSubroutineBody(): 存在语法错误, else不能单独出现..."<<endl;
        exit(1);
    }

    if(_JT->getTokenType() == SYMBOL && _JT->symbol() == '}'){
        outFile << "<symbol> } </symbol>" << endl;
    }
    outFile << "</subroutineBody>" << endl;
}

void CompilationEngine::compileVarDec(){
    outFile << "<varDec>" << endl;
    assert(_JT->getTokenType() == KEYWORD && (_JT->keyWord() == "var"));
    outFile << "<keyword> var </keyword>" << endl;

    _JT->advance();
    assert(_JT->getTokenType() == KEYWORD && (_JT->keyWord() == "int" || _JT->keyWord() == "char" || _JT->keyWord() == "boolean"));
    outFile << "<identifier>" << _JT->identifier() << "</identifier>" << endl;

    _JT->advance();
    assert(_JT->getTokenType() == IDENTIFIER);
    outFile << "<identifier>" << _JT->identifier() << "</identifier>" << endl;

    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ';');
    outFile << "<symbol> ; </symbol>" << endl;

    outFile << "</varDec>" << endl;
    _JT->advance();
}

void CompilationEngine::compileStatements(){
    outFile << "<statements>" << endl;
    while(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "let" || _JT->keyWord() == "if" || _JT->keyWord() == "else" || _JT->keyWord() == "while" || _JT->keyWord() == "do" || _JT->keyWord() == "return"){
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
        }
        else if(_JT->keyWord() == "return"){
            compileReturn();
        }
        else{
            cerr << "compileStatements(): 未知的keyword..."<<endl;
            exit(1);
        }
    }

    outFile << "</statements>" << endl;
}

void CompilationEngine::compileLet(){
    outFile << "<letStatement>" << endl;
    assert(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "let");
    outFile << "<keyword> let </keyword>" << endl;

    _JT->advance();
    assert(_JT->getTokenType() == IDENTIFIER);
    outFile << "<identifier> " << _JT->identifier() << " </identifier>" << endl;

    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '=');
    outFile << "<symbol> = </symbol>" << endl;

    _JT->advance();
    compileExpression();

    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ';');
    outFile << "<symbol> ; </symbol>" << endl;

    outFile << "</letStatement>" << endl;
    _JT->advance();
}

void CompilationEngine::compileIf(){
    outFile << "<ifStatement>"<<endl;
    assert(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "if");
    outFile << "<keyword> if </keyword>" << endl;

    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '(');
    outFile << "<symbol> ( </symbol>" << endl;

    _JT->advance();
    compileExpression();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
    outFile << "<symbol> ) </symbol>" << endl;
    
    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '{');
    outFile << "<symbol> { </symbol>" << endl;

    _JT->advance();
    compileStatements();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '}');
    outFile << "<symbol> } </symbol>" << endl;

    _JT->advance();
    if(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "else"){ //else是可选的
        outFile << "<keyword> else </keyword>" << endl;
        _JT->advance();
        assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '{');
        outFile << "<symbol> { </symbol>" << endl;

        _JT->advance();
        compileStatements();
        assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '}');
        outFile << "<symbol> } </symbol>" << endl;

        _JT->advance();
    }
    outFile << "/<ifStatement>"<<endl;
}

void CompilationEngine::compileWhile(){
    outFile << "<whileStatement>" << endl;
    assert(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "while");
    outFile << "<keyword> while </keyword>" << endl;

    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '(');
    outFile << "<symbol> ( </symbol>" << endl;

    _JT->advance();
    compileExpression();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
    outFile << "<symbol> ) </symbol>" << endl;

    _JT->advance();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '{');
    outFile << "<symbol> { </symbol>" << endl;

    _JT->advance();
    compileStatements();
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '}');
    outFile << "<symbol> } </symbol>" << endl;

    outFile << "</whileStatement>" << endl;
    _JT->advance();
}

void CompilationEngine::compileDo(){
    outFile << "<doStatement>" << endl;
    assert(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "do");
    outFile << "<keyword> do </keyword>" << endl;

    _JT->advance();
    assert(_JT->getTokenType() == IDENTIFIER);
    outFile << "<identifier> " << _JT->identifier() << "</identifier>" << endl;

    _JT->advance();
    if(_JT->getTokenType() == SYMBOL) {
        if(_JT->symbol() == '('){
            outFile << "<symbol> ( </symbol>" << endl;

            _JT->advance();
            compileExpressionList();

            assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
            outFile << "<symbol> ) </symbol>" << endl;
        }
        else if(_JT->symbol() == '.'){
            outFile << "<symbol> . </symbol>" << endl;

            _JT->advance();
            assert(_JT->getTokenType() == IDENTIFIER);
            outFile << "<identifier> " << _JT->identifier() << " </identifier>" << endl;

            _JT->advance();
            assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '(');
            outFile << "<symbol> ( </symbol>" << endl;

            _JT->advance();
            compileExpressionList();

            assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
            outFile << "<symbol> ) </symbol>" << endl;
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
    outFile << "</doStatement>" << endl;
    _JT->advance();
}

void CompilationEngine::compileReturn(){
    outFile << "<returnStatement>" << endl;
    assert(_JT->getTokenType() == KEYWORD && _JT->keyWord() == "return");
    outFile << "<keyword> return </keyword>" << endl;

    _JT->advance();
    if(_JT->getTokenType() != SYMBOL && _JT->symbol() != ';'){
        compileExpression();
    }
    assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ';');
    outFile << "</returnStatement>" << endl;
    _JT->advance();
}

void CompilationEngine::compileExpression(){
    outFile << "<expression>" << endl;
    compileTerm();

    _JT->advance();
    while(_JT->getTokenType() == SYMBOL){
        if(_JT->symbol() == ';' || _JT->symbol() == ')' || _JT->symbol() == ','){ //end of expression...maybe more!!!
            break;
        }
        else{ //other (op term)*
            if(_JT->symbol() == '>'){
                outFile << "<symbol> " << "&lt" << " </symbol>" <<endl;
            }
            else if(_JT->symbol() == '<'){
                outFile << "<symbol> " << "&gt" << " </symbol>" <<endl;
            }
            else if(_JT->symbol() == '&'){
                outFile << "<symbol> " << "&amp" << " </symbol>" <<endl;
            }
            else{
                outFile << "<symbol> " << _JT->symbol() << " </symbol>" <<endl;
            }
            _JT->advance();
            compileTerm();
            _JT->advance();
        }
    }
    outFile << "</expression>" << endl;
}

void CompilationEngine::compileTerm(){
    outFile << "<term>" << endl;

    if(_JT->getTokenType() == INT_CONST){
        outFile << "<integerConstant> " << _JT->intVal() << " </integerConstant>" << endl;  
    }
    else if(_JT->getTokenType() == STRING_CONST){
        outFile << "<stringConst> " << _JT->stringVal() << " </stringConst>" << endl;
    }
    else if(_JT->getTokenType() == KEYWORD){
        outFile << "<keyword> " << _JT->keyWord() << " </keyword>" << endl;
    }
    else if(_JT->getTokenType() == IDENTIFIER){
        outFile << "<identifier> " << _JT->identifier() << " </identifier>" << endl;

        Token nextToken = _JT->getNextToken();
        char nextChar = get<string>(nextToken.val)[0];
        if(nextChar == '('){ //bar(expressionList)
            _JT->advance();
            outFile << "<symbol> ( </symbol>" << endl;

            _JT->advance();
            compileExpressionList();
            assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
            outFile << "<symbol> ) </symbol>" << endl;
        }
        else if(nextChar == '.'){ //foo.bar(expressionList) or FOO.bar(expressionList)
            _JT->advance();
            outFile << "<symbol> . </symbol>" << endl;

            _JT->advance();
            assert(_JT->getTokenType() == IDENTIFIER);
            outFile << "<identifier> " << _JT->identifier() <<  " </identifier>" << endl;

            _JT->advance();
            assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == '(');
            outFile << "<symbol> ( </symbol>" << endl;

            _JT->advance();
            compileExpressionList();

            assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
            outFile << "<symbol> ) </symbol>" << endl;
        }
        else if(nextChar == '['){ //foo[expression]
            _JT->advance();
            outFile << "<symbol> [ </symbol>" << endl;
            
            _JT->advance();
            compileExpression();

            assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ']');
            outFile << "<symbol> ] </symbol>" << endl;
        }
        else{ 
            // op term的op 或者 )
        }
    }
    else{ //一些符号开头的term
        if(_JT->symbol() == '('){ //  (expression)
            outFile << "<symbol> ( </symbol>" << endl;
            
            _JT->advance();
            compileExpression();

            assert(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')');
            outFile << "<symbol> ) </symbol>" << endl;
        }
        else if(_JT->symbol() == '-' or _JT->symbol() == '~'){ //unary op:- ~
            outFile << "<symbol> " << _JT->symbol() << " </symbol>" << endl;
        }
        else{
            cerr << "compileTerm(): 错误的keyWord: " << _JT->keyWord() << endl;
            exit(1);
        }
    }
    outFile << "</term>" << endl;
}

void CompilationEngine::compileExpressionList(){
    outFile << "<expressionList>" << endl;
    if(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')'){
        outFile << "</expressionList>" << endl;
        return;
    }
    
    compileExpression();
    while(!(_JT->getTokenType() == SYMBOL && _JT->symbol() == ')')){
        _JT->advance();
        compileExpression();
    }
    outFile << "</expressionList>" << endl;

}


