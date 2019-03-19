//
//  History.cpp
//  Project 1
//
//  Created by Junhong Wang on 1/12/19.
//  Copyright © 2019 ioneone. All rights reserved.
//

#include <iostream>
#include "History.h"
#include "globals.h"
using namespace std;

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;
    data = new int[nRows * nCols];
    
    // initialize all data to 0
    for (int i = 0; i < nRows * nCols; i++)
        data[i] = 0;
}

History::~History()
{
    delete[] data;
}

bool History::record(int r, int c)
{
    if (1 <= r && r <= m_rows && 1 <= c && c <= m_cols) // check if r and c are within valid ranges
    {
        // Array index starts from 0
        if (data[m_cols * (r - 1) + (c - 1)] < 26) // 26 characters from A to Z
            data[m_cols * (r - 1) + (c - 1)]++;
        return true;
    }

    return false;
}

void History::display() const
{
    clearScreen();
    
    for (int i = 0; i < m_rows * m_cols; i++) {
        if (i % m_cols == 0)
            cout << '\n'; // wrap the line for each row
        if (data[i] == 0)
            cout << '.';
        else
            cout << (char) (data[i] + 64); // A is 65
        
    }
    
    cout << "\n\n";
    
}
