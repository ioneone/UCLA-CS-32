//
//  InflammableEnvironment.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/24/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef InflammableEnvironment_h
#define InflammableEnvironment_h

#include "MortalEnvironment.h"

class InflammableEnvironment: public MortalEnvironment {
public:
    InflammableEnvironment(StudentWorld *world, int imageID, double startX, double startY, int startLives, int startDirection = 0, int depth = 0);
    virtual ~InflammableEnvironment();
    
    virtual bool isAlive();
    virtual void die();
    
protected:
    void decrementLife();
    
private:
    int m_life;
};

#endif /* InflammableEnvironment_h */
