//
//  ImmortalActor.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/24/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef ImmortalActor_h
#define ImmortalActor_h

#include "Actor.h"

class ImmortalEnvironment: public Actor {
public:
    ImmortalEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startDirection, int depth);
    virtual ~ImmortalEnvironment();
    
    virtual void die();
    virtual bool isAlive();
    virtual bool isImmortal();
};

#endif /* ImmortalActor_h */
