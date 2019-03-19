//
//  TicTacToe.hpp
//  GameTutorial
//
//  Created by Junhong Wang on 12/13/18.
//  Copyright © 2018 ioneone. All rights reserved.
//

#ifndef TicTacToe_hpp
#define TicTacToe_hpp

#include <stdio.h>
#include "TTTPlayer.hpp"
#include "TTTBoard.hpp"

class TicTacToe {
public:
    TicTacToe();
    void start();
private:
    TTTPlayer *_player1;
    TTTPlayer *_player2;
    TTTBoard *_board;
    
    void initPlayers();
    void initBoard();
};

#endif /* TicTacToe_hpp */
