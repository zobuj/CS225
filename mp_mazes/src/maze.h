/* Your code here! */
#pragma once
#include <vector>
#include <unordered_map>
#include "dsets.h"
#include "cs225/PNG.h"
using namespace std;
using namespace cs225;
class SquareMaze{
    public:
    SquareMaze();//default constructor
    
     /*
    This uses your representation of the maze to determine whether it
    is possilble to travel in the given direction from the square at
    the coord (x,y).

    For example, after makeMaze(2,2), the possible input coord will be 
    (0,0),(0,1),(1,0),(1,1).
    IDEA: This means that we are going to have an inital if statement
    that checks if the input value is inbounds for the maze

        - dir = 0 represents a rightward step (+1 to the x coord)
        - dir = 1 represents 
    
        IDEA: we are not really updating the position, we are only
        checking if we can move to that location
        This means that we are going to have another if statement that
        checks if the movement is in bounds and that there is not a wall
        in that direction

        IDEA: storing a struct for each individual cells which will have
        a variable storing if the cell has walls
    


    Parameters:
        x - The x coordinate of the current cell
        y - The y coordinate of the current cell
        dir - The desired direction to move from the current cell
        IDEA: going to have to store a private variable for the maze
        width and height that gets intialized when we make the maze

    Returns:
        whether you can travel in the specified direction
        IDEA:probably going to return false in the end
    */
    bool canTravel(int x,int y, int dir) const;
    
    
    PNG * drawMaze() const;
    PNG * drawMazeWithSolution();
    void makeMaze(int width,int height);
    void setWall(int x,int y, int dir, bool exists);
    vector<int> solveMaze();
    private:
    int mazeWidth;
    int mazeHeight;
    typedef struct {
        //Perimeter Detector
        bool pU;
        bool pR;
        bool pD;
        bool pL;
        //Wall Detector
        bool down;
        bool right;
        //Coodinate Storage
        int xcoord;
        int ycoord;
        //index in allCells
        int index;
        //been visited checker
        bool visited;
    }cell;
    
    vector<cell> allCells;
    

    
};