/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "parser.h"
#include "program.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
    /* Empty */
}

Statement::~Statement() {
    /* Empty */
}
Statement *parseSta(TokenScanner &scanner,string s1) {
    string token = scanner.nextToken();
    if (token == "PRINT") {
        Statement *s;
        s = new Printsta(s1);
        return s;
    } else if (token == "LET") {
        Statement *s;
        s = new Letsta (s1);
        return s;
    } else if (token == "INPUT") {
        Statement *s;
        s = new Inputsta (s1);
        return s;
    } else if (token == "GOTO") {
        Statement *s;
        s = new Gotosta (s1);
        return s;
    } else if (token == "IF") {
        Statement *s;
        s = new Ifsta(s1);
        return s;
    }else if (token == "REM") {
        Statement *s;
        s = new Remsta(s1);
        return s;
    }else if (token == "END") {
        Statement *s;
        s = new Endsta;
        return s;
    }
}

void Printsta::execute(EvalState &state,Program &program,map<int, Statement *>::iterator &iter) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(s0);
    scanner.nextToken();
    Expression *exp = parseExp(scanner);
    int value = exp->eval(state);
    cout << value << endl;
    delete exp;
}

void Letsta::execute(EvalState &state,Program &program,map<int, Statement *>::iterator &iter) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(s0);
    scanner.nextToken();
    Expression *exp = parseExp(scanner);
    exp->eval(state);
    delete exp;
}

void Quitsta::execute(EvalState &state,Program &program,map<int, Statement *>::iterator &iter) {
    exit(0);
}
void Inputsta::execute(EvalState &state,Program &program,map<int, Statement *>::iterator &iter) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(s0);
    scanner.nextToken();
    bool flag = true;
    string vari = scanner.nextToken();
    string exp;
    while(1){
        flag = true;
        cout <<' ' << '?' << ' ';
        getline(cin,exp);
        if(exp[0] == '-'){
            for(int i = 1; i < exp.length(); ++i){
                if(exp[i] < '0' || exp[i] > '9') flag = false;
            }
        }
        else{
            for(int i = 0; i < exp.length(); ++i){
                if(exp[i] < '0' || exp[i] > '9') flag = false;
            }
        }
        if(!flag){
            cout << "INVALID NUMBER" << endl;
            continue;
        }
        if(exp[0] == '-') exp = '0' + exp;
        string Exp =vari + '=' + exp;
        TokenScanner scan;
        scan.ignoreWhitespace();
        scan.scanNumbers();
        scan.setInput(Exp);
        Expression *exp1 = parseExp(scan);
        exp1->eval(state);
        delete exp1;
        break;
    }
}

void Gotosta::execute(EvalState &state,Program &program,map<int, Statement *>::iterator &iter) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(s0);
    scanner.nextToken();
    string snumber = scanner.nextToken();
    int lineNumber0 = 0;
    for(int i = 0; i < snumber.length(); ++i){
        lineNumber0 *= 10;
        lineNumber0 += snumber[i] - '0';
    }
    iter = program.goTo(lineNumber0);
   if(iter == program.Pstate.end()) throw"LINE NUMBER ERROR";
}
void Ifsta::execute(EvalState &state,Program &program,map<int, Statement *>::iterator &iter) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(s0);
    scanner.nextToken();
    bool flag = false;
    string con;
    string nums;
    while(scanner.hasMoreTokens()){
        string s;
        s = scanner.nextToken();
        if(s != "THEN" && not flag) con += s;
        else if(s == "THEN") flag = true;
        else if(flag) nums = s;
    }
    int lineNumber = 0;
    for(int i = 0; i < nums.length(); ++i){
        lineNumber *= 10;
        lineNumber += nums[i] - '0';
    }
    if(checkcon(con,state)){
        iter = program.goTo(lineNumber);
        if(iter == program.Pstate.end()) throw"LINE NUMBER ERROR";
    }
}
void Endsta::execute(EvalState &state, Program &program, map<int, Statement *>::iterator &iter) {
    iter = program.Pstate.end();
}
void Remsta::execute(EvalState &state, Program &program,map<int, Statement *>::iterator &iter) {}
