//
//  eval.cpp
//  Homework 2
//
//  Created by Junhong Wang on 2/1/19.
//  Copyright © 2019 ioneone. All rights reserved.
//

// ==========================================
// #include lines you need, including "Set.h"
// ==========================================
#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

// ===============================================================
// declarations of any additional functions you might have written
// to help you evaluate an expression
// ===============================================================
bool isInfixSyntaxValid(const string& infix, string& operands);
int validateOperands(const string& operands, const Set& trueValues, const Set& falseValues);
void infixToPostfix(const string& infix, string& postfix);
bool isLowercaseAlphabet(const char& c);
bool isPrecedenceHigher(char op1, char op2);
void evaluatePostfix(const string& postfix, const Set& trueValues, bool& result);

// =======================
// evaluate implementation
// =======================
int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {
    string operands;

    if (!isInfixSyntaxValid(infix, operands)) return 1;

    int validation = validateOperands(operands, trueValues, falseValues);
    if (validation != 1) return validation; // 2 or 3

    infixToPostfix(infix, postfix);

    evaluatePostfix(postfix, trueValues, result);

    return 0;
}

// ==================================================================
// implementations of any additional functions you might have written
// to help you evaluate an expression
// ==================================================================

bool isInfixSyntaxValid(const string& infix, string& operands) {
    operands = "";
    char prevChar = ' ';
    int numOpenParanthesis = 0;
    int numCloseParanthesis = 0;

    for (char currChar : infix) {
        if (isLowercaseAlphabet(currChar)) {
            if (isLowercaseAlphabet(prevChar) || prevChar == ')') return false;
            operands += currChar;
        }
        else if (currChar == '(') {
            if (isLowercaseAlphabet(prevChar) || prevChar == ')') return false;
            numOpenParanthesis++;
        }
        else if (currChar == ')') {
            if (!isLowercaseAlphabet(prevChar) && prevChar != ')') return false;
            numCloseParanthesis++;
        }
        else if (currChar == '!') {
            if (isLowercaseAlphabet(prevChar) || prevChar == ')') return false;
        }
        else if (currChar == '&' || currChar == '|') {
            if (!isLowercaseAlphabet(prevChar) && prevChar != ')') return false;
        }
        else if (currChar == ' ') {
            // ignore space
            // prevChar will not be updated
            continue;
        }
        else {
            // check for invalid char
            return false;
        }

        prevChar = currChar;

    }

    // end with operator
    if (!isLowercaseAlphabet(prevChar) && prevChar != ')') return false;

    // paranthesis mismatch
    if (numOpenParanthesis != numCloseParanthesis) return false;

    return true;

}

int validateOperands(const string& operands, const Set& trueValues, const Set& falseValues) {
    for (char c : operands) {
        if (!trueValues.contains(c) && !falseValues.contains(c)) return 2;
        if (trueValues.contains(c) && falseValues.contains(c)) return 3;
    }

    return 1;
}

void infixToPostfix(const string& infix, string& postfix) {
    postfix = "";
    stack<char> operatorStack;

    // convert infix to postfix
    for (char c : infix) {
        if (isLowercaseAlphabet(c)) {
            postfix += c;
        }
        else if (c == '(') {
            operatorStack.push(c);
        }
        else if (c == ')') {
            while (operatorStack.top() != '(') {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
        }
        else if (c == '&' || c == '|' || c == '!') {
            while (!operatorStack.empty() && operatorStack.top() != '(' && !isPrecedenceHigher(c, operatorStack.top()) && !(c == '!' && operatorStack.top() == '!')) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c);
        }

    }

    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

}

bool isLowercaseAlphabet(const char& c) {
    return 'a' <= c && c <= 'z';
}

bool isPrecedenceHigher(char op1, char op2) {
    if (op1 == '!' && op2 != '!') return true;
    if (op1 == '&' && op2 == '|') return true;
    return false;
}

void evaluatePostfix(const string& postfix, const Set& trueValues, bool& result) {
    stack<bool> operandStack;
    bool op1, op2;
    for (char c : postfix) {
        if ('a' <= c && c <= 'z') {
            operandStack.push(trueValues.contains(c));
        }
        else {
            op2 = operandStack.top();
            operandStack.pop();
            if (c == '!') {
                operandStack.push(!op2);
            } else {
                op1 = operandStack.top();
                operandStack.pop();
                (c == '&') ? operandStack.push(op1 & op2) : operandStack.push(op1 | op2);
            }

        }
    }
    result = operandStack.top();
}

// ====================================
// a main routine to test your function
// ====================================
int main()
{
    string trueChars  = "tywz";
    string falseChars = "fnx";
    Set trues;
    Set falses;
    for (int k = 0; k < trueChars.size(); k++)
        trues.insert(trueChars[k]);
    for (int k = 0; k < falseChars.size(); k++)
        falses.insert(falseChars[k]);

    string pf;
    bool answer;
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  answer);
    assert(evaluate("y|", trues, falses, pf, answer) == 1);
    assert(evaluate("n t", trues, falses, pf, answer) == 1);
    assert(evaluate("nt", trues, falses, pf, answer) == 1);
    assert(evaluate("()", trues, falses, pf, answer) == 1);
    assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
    assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
    assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
    assert(evaluate("", trues, falses, pf, answer) == 1);
    assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
           &&  pf == "ff!tn&&|"  &&  !answer);
    assert(evaluate(" x  ", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  !answer);
    trues.insert('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 3);
    falses.erase('x');
    assert(evaluate("((x))", trues, falses, pf, answer) == 0  &&  pf == "x"  &&  answer);
    trues.erase('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 2);
    falses.insert('w');
    assert(evaluate("w| f", trues, falses, pf, answer) == 0  &&  pf == "wf|" &&  !answer);
    assert(evaluate("!!w", trues, falses, pf, answer) == 0 && pf == "w!!" && !answer);
    assert(evaluate("(w)&((w)", trues, falses, pf, answer) == 1);

    cout << "Passed all tests" << endl;
}
