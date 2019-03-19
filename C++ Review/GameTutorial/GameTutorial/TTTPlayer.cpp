//
//  TTTPlayer.cpp
//  GameTutorial
//
//  Created by Junhong Wang on 12/13/18.
//  Copyright © 2018 ioneone. All rights reserved.
//

#include "TTTPlayer.hpp"
#include <iostream>

TTTPlayer::TTTPlayer(string name, char symbol) {
    _name = name;
    _symbol = symbol;
}

string TTTPlayer::getName() {
    return _name;
}

char TTTPlayer::getSymbol() {
    return _symbol;
}

int* TTTPlayer::getMarkerPositions() {
    int x;
    int y;
    
    cout << "X: ";
    cin >> x;
    cout << "Y: ";
    cin >> y;
    
    return new int[2] { x, y };
    
}
