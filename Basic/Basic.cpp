/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"

using namespace std;

/* Function prototypes */

void processLine(string line, Program &program, EvalState &state);

/* Main program */
map<string,int> m0;
int main() {
    EvalState state;
    Program program;

    while (true) {
        try {
            string input = getLine();
            if (input.empty())
                return 0;
            processLine(input, program, state);
        }catch (const char *ex){
            cout << ex << endl;
        }
    }
    return 0;
}

void run(Program &program, EvalState &state){
    for(auto iter = program.getStart(); iter != program.getEnd();){
        int linen = iter->first;
        iter->second->execute(state,program,iter);
        if(iter->first == linen) ++iter;
        if(iter == program.getEnd()) break;
    }
}
/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    string token = scanner.nextToken();
    if (token == "RUN") {
        run(program,state);
    } else if (token == "PRINT") {
            Expression *exp = parseExp(scanner);
            int value = exp->eval(state);
            cout << value << endl;
            delete exp;
    }else if (token == "LET") {

        Expression *exp = parseExp(scanner);
        exp->eval(state);

        delete exp;
    } else if (token == "QUIT") {
        exit(0);
    } else if (token == "LIST") {
        program.List();
    }
    else if(token == "CLEAR"){//clear variables;
        program.clear();
        state.Clear();
    }
    else if(token == "INPUT"){
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
        string Exp ="LET "+ vari + '=' + exp;
        processLine(Exp,program,state);
        break;
    }
    }
        //有行号
    else if (token[0] <= '9' && token[0] >= '0') {
        int length = token.length();
        int lineNumber = 0;
        for (int i = 0; i < length; ++i) {
            lineNumber *= 10;
            lineNumber += token[i] - '0';
        }
        //删除一行
        if (!scanner.hasMoreTokens()) {
            program.removeSourceLine(lineNumber);
            delete program.getParsedStatement(lineNumber);
        } else {
            Statement *stmt;
            program.addSourceLine(lineNumber, line);
            program.setParsedStatement(lineNumber, stmt);
        }
    }
}

