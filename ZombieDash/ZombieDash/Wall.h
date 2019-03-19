//
//  Wall.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef Wall_h
#define Wall_h

#include "ImmortalEnvironment.h"

class Wall: public ImmortalEnvironment {
public:
    Wall(StudentWorld *world, int levelX, int levelY);
    virtual ~Wall();
    
    virtual void doSomething();
    virtual bool isFlameBlockable();
};

#endif /* Wall_h */
