//
//  Exit.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/17/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef Exit_h
#define Exit_h

#include "ImmortalEnvironment.h"

class Exit: public ImmortalEnvironment {
public:
    Exit(StudentWorld *world, int levelX, int levelY);
    virtual void doSomething();
    virtual bool isOverlappable();
    virtual ~Exit();
    virtual bool isFlameBlockable();
};

#endif /* Exit_h */
