#pragma once
#include <vector>
#include "dsets.h"
#include "cs225/PNG.h"
using namespace cs225;
class SquareMaze{
    public:
    SquareMaze();

    void makeMaze(int width,int height);

    bool canTravel(int x, int y, int dir) const;

    PNG * drawMaze()const;
    
    PNG * drawMazeWithSolution();
    
    void setWall(int x, int y, int dir, bool exists);
    
    std::vector<int> solveMaze();

    private:
    int mazeHeight;
    int mazeWidth;
    int mazeSize;
    typedef struct{
        bool right;
        bool down;
        int index;
        int xcoord;
        int ycoord;
    }Cell;
    std::vector<Cell> allCells;
};