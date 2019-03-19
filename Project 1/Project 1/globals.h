//
//  globals.h
//  Project 1
//
//  Created by Junhong Wang on 1/12/19.
//  Copyright © 2019 ioneone. All rights reserved.
//

#ifndef globals_h
#define globals_h

const int MAXROWS = 20;              // max number of rows in the arena
const int MAXCOLS = 30;              // max number of columns in the arena
const int MAXZOMBIES = 150;          // max number of zombies allowed
const int INITIAL_ZOMBIE_HEALTH = 2;

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

int randInt(int min, int max);
void clearScreen();

#endif /* globals_h */
