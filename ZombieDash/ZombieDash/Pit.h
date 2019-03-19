//
//  Pit.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef Pit_h
#define Pit_h

#include "ImmortalEnvironment.h"

class Pit: public ImmortalEnvironment {
public:
    Pit(StudentWorld *world, double startX, double startY);
    Pit(StudentWorld *world, int levelX, int levelY);
    virtual ~Pit();
    
    virtual void doSomething();
    virtual bool isOverlappable();
};

#endif /* Pit_h */
