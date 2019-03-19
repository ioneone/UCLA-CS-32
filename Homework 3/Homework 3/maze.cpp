//
//  maze.cpp
//  Homework 3
//
//  Created by Junhong Wang on 2/6/19.
//  Copyright © 2019 ioneone. All rights reserved.
//

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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    if (sr == er && sc == ec) return true;

    maze[sr][sc] = 'X';

    int r;
    int c;

    // SOUTH
    r = sr + 1;
    c = sc;
    if (r < nRows && maze[r][c] != 'X') {
        if (pathExists(maze, nRows, nCols, r, c, er, ec)) return true;
    }

    // WEST
    r = sr;
    c = sc - 1;
    if (c >= 0 && maze[r][c] != 'X') {
        if (pathExists(maze, nRows, nCols, r, c, er, ec)) return true;
    }

    // NORTH
    r = sr - 1;
    c = sc;
    if (r >= 0 && maze[r][c] != 'X') {
        if (pathExists(maze, nRows, nCols, r, c, er, ec)) return true;
    }

    // EAST
    r = sr;
    c = sc + 1;
    if (c < nCols && maze[r][c] != 'X') {
        if (pathExists(maze, nRows, nCols, r, c, er, ec)) return true;
    }

    return false;
}
