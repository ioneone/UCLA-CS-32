//
//  FlammableEnvironment.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/24/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef FlammableEnvironment_h
#define FlammableEnvironment_h

#include "MortalEnvironment.h"

class FlammableEnvironment: public MortalEnvironment {
public:
    FlammableEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startDirection = 0, int depth = 0);
    virtual ~FlammableEnvironment();
    
    virtual bool isFlammable();
    virtual void die();
    virtual bool isAlive();
private:
    bool m_isAlive;
};

#endif /* FlammableEnvironment_h */
