//
//  Monster.cpp
//  GameTutorial
//
//  Created by Junhong Wang on 12/13/18.
//  Copyright © 2018 ioneone. All rights reserved.
//

#include "Monster.hpp"
#include <iostream>

Monster::Monster() {
    _name = "NONAME";
}

Monster::Monster(string name) {
    _name = name;
}

void Monster::printName() {
    cout << "My name is " <<  _name << endl;
}
