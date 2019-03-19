//
//  TTTBoard.cpp
//  GameTutorial
//
//  Created by Junhong Wang on 12/13/18.
//  Copyright © 2018 ioneone. All rights reserved.
//

#include "TTTBoard.hpp"
#include <iostream>

using namespace std;

TTTBoard::TTTBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            _board[i][j] = '-';
        }
    }
}

char TTTBoard::check() {
    for (int i = 0; i < 3; i++) {
        if (_board[i][0] == _board[i][1] && _board[i][1] == _board[i][2]) {
            return _board[i][0];
        }
    }
    
    for (int j = 0; j < 3; j++) {
        if (_board[0][j] == _board[1][j] && _board[1][j] == _board[2][j]) {
            return _board[0][j];
        }
    }
    
    if (_board[0][0] == _board[1][1] && _board[1][1] == _board[2][2]) {
        return _board[0][0];
    }
    
    if (_board[0][2] == _board[1][1] && _board[1][1] == _board[2][0]) {
        return _board[0][2];
    }
    
    return '-';
}

void TTTBoard::addMarker(char marker, int x, int y) {
    _board[y][x] = marker;
}

void TTTBoard::print() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << _board[i][j];
        }
        cout << endl;
    }
}
