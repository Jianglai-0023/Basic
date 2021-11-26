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
Statement *parseSta(TokenScanner &scanner){
    string token = scanner.nextToken();
//    if(token[0] >= '0' && token[0] <= '9'){
//        if(program.Prom.find(int(token))){

        }
//    }
//    if(token == "RUN"){
//        exit(0);
//    }
//    else if(token == "PRINT"){
//        string s = scanner.nextToken();
//        if(s[0] <='9' && s[0] >='0'){
//            cout << s << endl;
//        }
//        else{
//            Expression *exp = parseExp(scanner);
//            int value = exp->eval(state);
//            cout << value << endl;
//        }
//    }
//    else if(token == "LIST"){};
//    else if(token == "CLEAR"){};
//    else if(token == "QUITE"){
//        exit(0);
//    }
//    else if(token == "HELP"){
//
//    }
//
//
//    else if(token == "PRINT"){
//        //变量或数字或
//       cout << token.nextToken;
//    }
//
//    else if(token == "LET"){
//        Expression *exp = parseExp(scanner);
//    }
//};