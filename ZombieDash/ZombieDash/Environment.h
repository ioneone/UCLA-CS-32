//
//  Environment.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/24/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef Environment_h
#define Environment_h

#include "Actor.h"

class Environment: public Actor {
public:
    Environment(StudentWorld *world, int imageID, double startX, double startY, int startDirection = 0, int depth = 0);
    virtual ~Environment();
    
    virtual bool isEnvironment();
};


#endif /* Environment_h */
