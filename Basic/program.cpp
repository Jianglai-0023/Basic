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
map<int, string>::iterator Program::getStart(){
    return Promsta.begin();
}
map<int, string>::iterator Program::getEnd(){
    return Promsta.end();
}
map<int, string>::iterator Program::goTo(const int &lineNumber){
//    cout << lineNumber <<"*" << endl;
    return Promsta.find(lineNumber);

}
void Program::addSourceLine(int lineNumber, string line) {
    Promstr[lineNumber] = line;
    Promsta[lineNumber] = getState(lineNumber);
//    cout << Promsta[lineNumber] << endl;
}

void Program::removeSourceLine(int lineNumber) {
    if(hasline(lineNumber)) {
        auto iter = Promstr.find(lineNumber);
        auto iter2 = Promsta.find(lineNumber);
        Promstr.erase(iter);
        Promsta.erase(iter2);
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
    // Replace this stub with your own code
}

Statement *Program::getParsedStatement(int lineNumber) {
    return NULL;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {

    return 0;     // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
    return 0;     // Replace this stub with your own code
}
