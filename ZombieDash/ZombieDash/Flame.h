//
//  Flame.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef Flame_h
#define Flame_h

#include "InflammableEnvironment.h"

class Flame: public InflammableEnvironment {
public:
    Flame(StudentWorld *world, double startX, double startY, int direction);
    virtual ~Flame();
    
    virtual void doSomething();
    
};

#endif /* Flame_h */
