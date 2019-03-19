//
//  Landmine.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef Landmine_h
#define Landmine_h

#include "FlammableEnvironment.h"

class Landmine: public FlammableEnvironment {
public:
    Landmine(StudentWorld *world, double startX, double startY);
    virtual void doSomething();
    virtual ~Landmine();
    
private:
    void updateSafetyTicks();
    void explode();
    bool isActive() const;
    int m_numSafetyTicks;
};

#endif /* Landmine_h */
