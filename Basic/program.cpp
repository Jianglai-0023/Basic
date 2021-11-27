/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "parser.h"
#include "evalstate.h"
#include "exp.h"
using namespace std;

Program::Program() {

}

Program::~Program() {
    // Replace this stub with your own code
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

bool Program::hasline(int lineNumber){
    if(Promstr.count(lineNumber)) return true;
    return false;
}

void Program::clear() {
    Promstr.clear();
}
void Program::List(){
    for(auto iter = Promstr.begin(); iter != Promstr.end(); ++iter){
        cout << iter->second << endl;
    }
}
map<int, Statement *>::iterator Program::getStart(){
    return Pstate.begin();
}
map<int, Statement *>::iterator Program::getEnd(){
    return Pstate.end();
}
map<int, Statement *>::iterator Program::goTo(const int &lineNumber){

    return Pstate.find(lineNumber);

}
void Program::addSourceLine(int lineNumber, string line) {
    Statement *stmt;
    Promstr[lineNumber] = line;
    Promsta[lineNumber] = getState(lineNumber);
    setParsedStatement(lineNumber, stmt);
}

void Program::removeSourceLine(int lineNumber) {
    if(hasline(lineNumber)) {
        auto iter = Promstr.find(lineNumber);
        auto iter2 = Promsta.find(lineNumber);
        auto iter3 = Pstate.find(lineNumber);
        Promstr.erase(iter);
        Promsta.erase(iter2);
        Pstate.erase(iter3);
    }
}

string Program::getState(int lineNumber) {
    string ori = Promstr[lineNumber];
    string sta;
    int j = 0;
    int i = 0;
    for(i = 0; i < ori.length(); ++i){
        if(ori[i] == ' ') {
            break;
        }
    }
    for (j = i + 1; j < ori.length(); ++j){
        sta += ori[j];
    }
    return sta;
}

string Program::getSourceLine(int lineNumber) {
    string s;
    s = Promstr[lineNumber];
    return s;    // Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    TokenScanner scan;
    scan.ignoreWhitespace();
    scan.scanNumbers();
    scan.setInput(Promsta[lineNumber]);
    stmt = parseSta(scan,Promsta[lineNumber]);
    Pstate[lineNumber] = stmt;
}

Statement *Program::getParsedStatement(int lineNumber) {
    return Pstate[lineNumber];
}

int Program::getFirstLineNumber() {

    return 0;     // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
    return 0;     // Replace this stub with your own code
}
