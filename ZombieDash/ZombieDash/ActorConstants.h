//
//  ActorConstants.h
//  ZombieDash
//
//  Created by Junhong Wang on 2/19/19.
//  Copyright © 2019 David Smallberg. All rights reserved.
//

#ifndef ActorConstants_h
#define ActorConstants_h

#include "GraphObject.h"

// Step
const double PENELOPE_STEP = 4;
const double ZOMBIE_STEP   = 1;
const double CITIZEN_STEP  = 2;

// Start Direction
const int PENELOPE_START_DIRECTION = GraphObject::right;
const int WALL_START_DIRECTION     = GraphObject::right;
const int EXIT_START_DIRECTION     = GraphObject::right;
const int PIT_START_DIRECTION      = GraphObject::right;
const int GOODIE_START_DIRECTION   = GraphObject::right;
const int LANDMINE_START_DIRECTION = GraphObject::right;
const int ZOMBIE_START_DIRECTION   = GraphObject::right;
const int CITIZEN_START_DIRECTION  = GraphObject::right;

// Depth
const int PENELOPE_DEPTH = 0;
const int WALL_DEPTH     = 0;
const int EXIT_DEPTH     = 1;
const int PIT_DEPTH      = 0;
const int FLAME_DEPTH    = 0;
const int VOMIT_DEPTH    = 0;
const int GOODIE_DEPTH   = 1;
const int LANDMINE_DEPTH = 1;
const int ZOMBIE_DEPTH   = 0;
const int CITIZEN_DEPTH  = 0;

// Infection Count
const int MAX_INFECTION_COUNT = 500;

// Scores
const int EXIT_SCORE                 = 500;
const int GOODIE_SCORE               = 50;
const int DUMB_ZOMBIE_SCORE          = 1000;
const int SMART_ZOMBIE_SCORE         = 2000;
const int CITIZEN_DEAD_PENALTY_SCORE = -1000;


// Life
const int START_FLAME_LIVES = 2;
const int START_VOMIT_LIVES = 2;

// Charges
const int CHARGES_PER_VACCINE_GOODIE = 1;
const int CHARGES_PER_GAS_CAN_GOODIE = 5;
const int CHARGES_PER_LANDMINE_GOODIE = 2;

// Safety Ticks
const int LANDMINE_START_SAFETY_TICKS = 30;

// Probabilities
const double VOMIT_PROBABILITY               = 0.3;
const double DUMB_ZOMBIE_PROBABILITY         = 0.7;
const double VACCINE_GOODIE_DROP_PROBABILITY = 0.1;

// Distances
const double OVERLAP_EUCLIDEAN_DISTANCE  = 10;
const double CITIZEN_VISION_DISTANCE     = 80;
const double SMART_ZOMBIE_VISION_DISTANE = 80;

const int ZOMBIE_MOVEMENT_PLAN_MIN = 3;
const int ZOMBIE_MOVEMENT_PLAN_MAX = 10;

#endif /* ActorConstants_h */
