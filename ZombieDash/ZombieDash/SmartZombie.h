//
//  SmartZombie.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef SmartZombie_h
#define SmartZombie_h

#include "Zombie.h"

class SmartZombie: public Zombie {
public:
    SmartZombie(StudentWorld *world, double startX, double startY);
    SmartZombie(StudentWorld *world, int levelX, int levelY);
    virtual ~SmartZombie();
    virtual int score();
protected:
    virtual void planMovement();
};

#endif /* SmartZombie_h */
