//
//  TicTacToe.cpp
//  GameTutorial
//
//  Created by Junhong Wang on 12/13/18.
//  Copyright © 2018 ioneone. All rights reserved.
//

#include "TicTacToe.hpp"
#include <iostream>
#include <string>

TicTacToe::TicTacToe() {
    string player1Name;
    char player1Symbol;
    string player2Name;
    char player2Symbol;

    cout << "Welcome to TicTacToe Lite!" << endl;

    cout << "The first player should now enter their name: ";
    cin >> player1Name;
    cout << "Hello " << player1Name << "!" << endl;
    cout << "What would you like your symbol be?: ";
    cin >> player1Symbol;

    cout << "The next player should now enter their name: ";
    cin >> player2Name;
    cout << "Hello " << player2Name << "!" << endl;
    cout << "What would you like your symbol be?: ";
    cin >> player2Symbol;

    _player1 = new TTTPlayer(player1Name, player1Symbol);
    _player2 = new TTTPlayer(player2Name, player2Symbol);
    
    _board = new TTTBoard();

}

void TicTacToe::start() {
    bool isDone = false;
    bool isPlayer1Turn = true;
    
    _board->print();
    
    while (!isDone) {
        
        
        if (isPlayer1Turn) {
            int *positions = _player1->getMarkerPositions();
            _board->addMarker(_player1->getSymbol(), positions[0], positions[1]);
        } else {
            int *positions = _player2->getMarkerPositions();
            _board->addMarker(_player2->getSymbol(), positions[0], positions[1]);
        }
        
        isPlayer1Turn = !isPlayer1Turn;
        
        _board->print();
        
        char check = _board->check();
        if (check != '-') {
            isDone = true;
            if (check == _player1->getSymbol()) {
                cout << _player1->getName() << " won." << endl;
            } else {
                cout << _player2->getName() << " won." << endl;
            }
        }
    }
}
