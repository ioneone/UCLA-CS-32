//
//  Monster.hpp
//  GameTutorial
//
//  Created by Junhong Wang on 12/13/18.
//  Copyright © 2018 ioneone. All rights reserved.
//

#ifndef Monster_hpp
#define Monster_hpp

#include <string>

using namespace std;

class Monster {
public:
    Monster();
    Monster(string name);
    void printName();
    
private:
    string _name;
};

#endif /* Monster_hpp */
