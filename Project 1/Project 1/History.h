//
//  History.h
//  Project 1
//
//  Created by Junhong Wang on 1/12/19.
//  Copyright © 2019 ioneone. All rights reserved.
//

#ifndef History_h
#define History_h

class History
{
public:
    History(int nRows, int nCols);
    ~History();
    bool record(int r, int c);
    void display() const;

private:
    int  m_rows;
    int  m_cols;
    int* data; // data contains information about the number of Zombies died
               // and their last locations in the Arena
    
};

#endif /* History_h */
