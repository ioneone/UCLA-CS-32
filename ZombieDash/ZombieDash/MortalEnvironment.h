//
//  MortalEnvironment.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/24/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef MortalEnvironment_h
#define MortalEnvironment_h

#include "Environment.h"

class MortalEnvironment: public Environment {
public:
    MortalEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startDirection = 0, int depth = 0);
    virtual ~MortalEnvironment();
    
    virtual bool isOverlappable();
};

#endif /* MortalEnvironment_h */
