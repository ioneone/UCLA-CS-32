//
//  TTTPlayer.hpp
//  GameTutorial
//
//  Created by Junhong Wang on 12/13/18.
//  Copyright © 2018 ioneone. All rights reserved.
//

#ifndef TTTPlayer_hpp
#define TTTPlayer_hpp

#include <stdio.h>
#include <string>

using namespace std;

class TTTPlayer {
public:
    TTTPlayer(string name, char symbol);
    string getName();
    char getSymbol();
    int* getMarkerPositions();
private:
    string _name;
    char _symbol;
    
};

#endif /* TTTPlayer_hpp */
