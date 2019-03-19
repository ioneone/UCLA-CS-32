//
//  Vomit.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef Vomit_h
#define Vomit_h

#include "InflammableEnvironment.h"

class Vomit: public InflammableEnvironment {
public:
    Vomit(StudentWorld *world, double startX, double startY, int direction);
    virtual ~Vomit();
    
    virtual void doSomething();
    
};

#endif /* Vomit_h */
