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
//bool dbyzero = false;
/* Main program */
map<string,int> m0;
int main() {
    EvalState state;
    Program program;
//    cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            string input = getLine();
            if (input.empty())
                return 0;
            processLine(input, program, state);
        }catch (const char *ex){
            cout << ex << endl;
        }
//        } catch (ErrorException &ex) {
//            cerr << ex.getMessage() << endl;
//        }
    }
    return 0;
}
bool checkcon(string s,EvalState &state){
    TokenScanner ex1;
    TokenScanner ex2;
     string exp1;
     string exp2;
     int l,r;
     char comp;
     bool j = false;
     for(int i = 0; i < s.length(); ++i){
         if(s[i] != '<' && s[i]!= '>' &&  s[i] != '=' && !j) exp1 += s[i];
         else if(j && s[i] != '<' && s[i]!= '>' && s[i] != '=') exp2 += s[i];
         else if(s[i] == '<' || s[i] == '=' || s[i] == '>') comp = s[i], j = true;
     }
     ex1.setInput(exp1);
     ex2.setInput(exp2);
    Expression *e1 = parseExp(ex1);
    l = e1->eval(state);
    Expression *e2 = parseExp(ex2);
    r = e2->eval(state);
    if(comp == '=') return (l == r);
    if(comp == '<') return (l < r);
    if(comp == '>') return (l > r);
}
void run(Program &program, EvalState &state){
    TokenScanner scan;
    scan.ignoreWhitespace();
    scan.scanNumbers();
    for(auto iter = program.getStart(); iter != program.getEnd();){
        scan.setInput(iter->second);
        string token = scan.nextToken();
        ++iter;
        if (token == "PRINT") {
            Expression *exp = parseExp(scan);
            int value = exp->eval(state);
            cout << value << endl;
            delete exp;
        }else if (token == "LET") {

            Expression *exp = parseExp(scan);
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
            string vari = scan.nextToken();
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
        else if(token == "GOTO"){
            string snumber = scan.nextToken();
            int lineNumber0 = 0;
            for(int i = 0; i < snumber.length(); ++i){
                lineNumber0 *= 10;
                lineNumber0 += snumber[i] - '0';
            }
            iter = program.goTo(lineNumber0);
            if(iter == program.Promsta.end()) throw"LINE NUMBER ERROR";
//            cout << lineNumber0 << "%%" << endl;
//            cout << (iter == program.Promsta.end()) << "&*&" << endl;
        }
        else if(token == "IF"){
            bool flag = false;
           string con;
           string nums;
           while(scan.hasMoreTokens()){
               string s;
               s = scan.nextToken();
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
            }
        }
        else if(token == "END"){
            break;
        }
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
        } else {
            program.addSourceLine(lineNumber, line);
        }


//    Expression *exp = parseExp(scanner);
//    int value = exp->eval(state);
//    cout << value << endl;
//    delete sta;
//    delete exp;
    }
}

