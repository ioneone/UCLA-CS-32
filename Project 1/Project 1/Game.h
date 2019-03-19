//
//  Game.h
//  Project 1
//
//  Created by Junhong Wang on 1/12/19.
//  Copyright © 2019 ioneone. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include "Arena.h"

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
    // Auxiliary function declarations
    int decodeDirection(char dir);
    
private:
    Arena* m_arena;
};

#endif /* Game_h */
