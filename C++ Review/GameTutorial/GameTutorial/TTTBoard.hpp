//
//  TTTBoard.hpp
//  GameTutorial
//
//  Created by Junhong Wang on 12/13/18.
//  Copyright © 2018 ioneone. All rights reserved.
//

#ifndef TTTBoard_hpp
#define TTTBoard_hpp

#include <stdio.h>

class TTTBoard {
public:
    TTTBoard();
    char check();
    void addMarker(char marker, int x, int y);
    void print();
private:
    char _board[3][3];
};

#endif /* TTTBoard_hpp */
