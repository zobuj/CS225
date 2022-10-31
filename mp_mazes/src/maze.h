#pragma once
#include <vector>
#include "dsets.h"
#include "cs225/PNG.h"
using namespace cs225;

class SquareMaze{
    public:
    SquareMaze();

    bool canTravel(int x, int y, int dir) const;

    PNG * drawMaze()const;
    
    PNG * drawMazeWithSolution();
    
    void makeMaze(int width, int height);
    
    void setWall(int x, int y, int dir, bool exists);
    
    std::vector<int> solveMaze();
    
    private:
    int mazeHeight;
    int mazeWidth;
    typedef struct{
        bool rightWall;
        bool downWall;
        int xcoord;
        int ycoord;
        int index;
    }Cell;
    std::vector<Cell> allCells;

};