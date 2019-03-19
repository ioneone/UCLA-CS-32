//
//  mazequeue.cpp
//  Homework 2
//
//  Created by Junhong Wang on 2/1/19.
//  Copyright © 2019 ioneone. All rights reserved.
//

#include <string>
#include <queue>
#include <iostream>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    queue<Coord> coordQueue;
    Coord start(sr, sc);
    coordQueue.push(start);
    maze[sr][sc] = 'X';

//    int count = 1;
    while (!coordQueue.empty()) {
        Coord curr = coordQueue.front();

//        cout << count << ": (" << curr.r() << ", " << curr.c() << ")" << endl;
//        count++;

        coordQueue.pop();
        if (curr.r() == er && curr.c() == ec) return true;

        int r;
        int c;

        // SOUTH
        r = curr.r() + 1;
        c = curr.c();
        if ((r < nRows) && maze[r][c] != 'X') {
            coordQueue.push(Coord(r, c));
            maze[r][c] = 'X';
        }

        // WEST
        r = curr.r();
        c = curr.c() - 1;
        if (c >= 0 && maze[r][c] != 'X') {
            coordQueue.push(Coord(r, c));
            maze[r][c] = 'X';
        }

        // NORTH
        r = curr.r() - 1;
        c = curr.c();
        if (r >= 0 && maze[r][c] != 'X') {
            coordQueue.push(Coord(r, c));
            maze[r][c] = 'X';
        }

        // EAST
        r = curr.r();
        c = curr.c() + 1;
        if (c < nCols && maze[r][c] != 'X') {
            coordQueue.push(Coord(r, c));
            maze[r][c] = 'X';
        }

    }

    return false;
}

int main() {
    string maze[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "X.XX.XX..X",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10,10, 3,5, 8,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

