#include "maze.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
using namespace std;
SquareMaze::SquareMaze(){
    mazeWidth=0;
    mazeHeight=0;
}
void SquareMaze::makeMaze(int width,int height){
    mazeWidth=width;
    mazeHeight=height;
    mazeSize = width*height;
    DisjointSets cycleCells;
    cycleCells.addelements(mazeSize);
    for(int w  = 0;w<mazeWidth;w++){
        for(int h = 0;h<mazeHeight;h++){
            Cell c;
            c.right=true;
            c.down=true;
            c.xcoord=w;
            c.ycoord=h;
            c.index=w*mazeHeight+h;
            allCells.push_back(c);
            /*cout<<c.index;
            if(c.down==true){
                cout<<"_";
            }
            if(c.right==true){
                cout<<"|";
            }*/
        }
        //cout<<endl;
    }
    int numTrees = mazeSize;
    //srand(time(NULL));
    while(numTrees>1){
        int cellIndex = rand()%(mazeSize);//picks a random number within the bounds of the index of the maze
        //sleep_for(nanoseconds(10));
        //sleep_until(system_clock::now() + seconds(1));
        int dir;

        //if the x or y coord exist on the bounds of the maze then we can choose their direction accordingly

        if(allCells[cellIndex].xcoord==mazeWidth-1 && allCells[cellIndex].ycoord==mazeHeight-1){
            //cout<<"Located on bottomright: "<<cellIndex<<endl;
            continue;
        }
        else if(allCells[cellIndex].xcoord==mazeWidth-1){
            //if located on the bottom of the matrix must move to the right
            dir=0;
            //cout<<"Located on bottom: "<<cellIndex<<endl;
            //cout<<"dir: "<<dir<<endl;
        }
        else if(allCells[cellIndex].ycoord==mazeHeight-1){
            //if located on the right of the matrix must move down
            //cout<<"Located on right: "<<cellIndex<<endl;
            dir=1;
            //cout<<"dir: "<<dir<<endl;
        }
        else{
            //if the the cell does not exist at any point on the border then we can just choose a random direction
            //cout<<"not located on bound: "<<cellIndex<<endl;
            dir = rand()%2;
            //cout<<"dir: "<<dir<<endl;
        }    
        if(dir==0){//move right
            if(cycleCells.find(cellIndex)!=cycleCells.find(cellIndex+1)){
                allCells[cellIndex].right=false;
                cycleCells.setunion(cellIndex,cellIndex+1); 
                numTrees--;
            }
        }else if(dir==1){//move down
            if(cycleCells.find(cellIndex)!=cycleCells.find(cellIndex+mazeWidth)){
                allCells[cellIndex].down=false;
                cycleCells.setunion(cellIndex,cellIndex+mazeWidth); 
                numTrees--;
            }
        }
        /*cycleCells.printAllNodes();
        cout<<"NumTrees: "<<numTrees<<endl;
        cout<<"allcells[0] right and down walls: "<<allCells[0].right<<" , "<<allCells[0].down<<endl;
        cout<<"allcells[1] right and down walls: "<<allCells[1].right<<" , "<<allCells[1].down<<endl;
        cout<<"allcells[2] right and down walls: "<<allCells[2].right<<" , "<<allCells[2].down<<endl;
        cout<<"allcells[3] right and down walls: "<<allCells[3].right<<" , "<<allCells[3].down<<endl;
        */


    }
    
}
bool SquareMaze::canTravel(int x, int y, int dir) const {
    int index =y*mazeHeight+x;
    if(dir==0){//move right
        if(x>=mazeHeight-1){
            return false;
        }
        if(allCells[index].right==true){
            return false;
        }
        return true;
    }else if(dir==1){//move down
        if(y>=mazeWidth-1){
            return false;
        }
        if(allCells[index].down==true){
            return false;
        }
        return true;
    }else if(dir==2){//move left
        if(x==0){
            return false;
        }
        if(allCells[index-1].right==true){
            return false;
        }
        return true;
    }else if(dir==3){//move up
        if(y==0){
            return false;
        }
        if(allCells[index-mazeWidth].down==true){
            return false;
        }
        return true;
    }
    return false;
}
 
PNG * SquareMaze::drawMazeWithSolution(){
    PNG * im = nullptr;
    return im;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if(dir==0){
        allCells[y*mazeHeight+x].right=exists;
    }else if(dir==1){
        allCells[y*mazeHeight+x].down=exists;
    }
}
std::vector<int> SquareMaze::solveMaze(){
    std::vector<int> vec;
    int originCell = allCells[0];
    
    for(int i =0)
    return vec;
}
PNG * SquareMaze::drawMaze()const{
    PNG * result = new PNG(mazeWidth * 10 + 1, mazeHeight * 10 + 1);
	return result;
}