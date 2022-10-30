/* Your code here! */
#include "maze.h"
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <thread>
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
SquareMaze::SquareMaze(){
    /*Creates an empty maze*/
}
void SquareMaze::makeMaze(int width,int height){

    mazeWidth = width;//store the width
    mazeHeight = height;//store the height
    DisjointSets cycleCells;//store a disjoint set 
    cycleCells.addelements(mazeWidth*mazeHeight);//store a representative node for each cell

    /*Construct a maze with all the walls in place*/
    for(int w = 0;w<mazeWidth;w++){
        for(int h = 0;h<mazeHeight;h++){
            cell x;
            x.right=true;
            x.down=true;
            x.pU=false;
            x.pR=false;
            x.pD=false;
            x.pL=false;

            if(w==0){
                if(h==0){
                    x.pU=true;
                    x.pL=true;
                }else if(h==(mazeHeight-1)){
                    x.pU=true;
                    x.pR=true;
                }else{
                    x.pU=true;
                }
            }
            if(w == (mazeWidth-1)){
                if(h==0){
                    x.pL=true;
                    x.pD=true;
                }else if(h==(mazeHeight-1)){
                    x.pD=true;
                    x.pR=true;
                }else{
                    x.pD=true;  
                }
            }
            if(h==0){
                if(w==0){
                    x.pL=true;
                    x.pU=true;
                }else if(w==(mazeWidth-1)){
                   x.pL=true;
                    x.pD=true;
                }else{
                    x.pL=true;
                }
            }
            if(h==(mazeHeight-1)){
                if(w==0){
                    x.pR=true;
                    x.pU=true;
                }else if(w==(mazeWidth-1)){
                   x.pR=true;
                    x.pD=true;
                }else{
                    x.pR=true;
                }
            }
            x.xcoord = w;
            x.ycoord = h;
            x.index = w*mazeHeight+h;
            x.visited=false;
            allCells.push_back(x);
            /*cout<<"Xcoord: "<<allCells[x.index].xcoord<<" Ycoord: "<<allCells[x.index].ycoord<<endl;
            cout<<"Down: "<<allCells[x.index].down<<" Right: "<<allCells[x.index].right<<endl;
            cout<<"pU: "<<allCells[x.index].pU<<" pR: "<<allCells[x.index].pR<<" pD: "<<allCells[x.index].pD<<" pL: "<<allCells[x.index].pL<<endl;
            cout<<"Index: "<<allCells[x.index].index<<endl;
            
            cout<<endl;*/

        }
    }
    
    /*Randomly select walls to delete*/
    
    //1. Choose a random cell
    cell currentCell;
    
    int numTrees = cycleCells.getNumTrees();
    while(numTrees>1){
        cycleCells.printAllNodes();
        /*cout<<"Current Index: "<<currentCell.index<<endl;
        cout<<"Current x and y coord: "<<currentCell.xcoord<<" , "<<currentCell.ycoord<<endl;
        cout<<"Current Has right perimeter: "<<currentCell.pR<<endl;
        cout<<"Current Has down perimeter: "<<currentCell.pD<<endl;
        cout<<"Current Has up perimeter: "<<currentCell.pU<<endl;
        cout<<"Current Has left perimeter: "<<currentCell.pL<<endl;
        cout<<"allcells[0] right and down walls: "<<allCells[0].right<<" , "<<allCells[0].down<<endl;
        cout<<"allcells[1] right and down walls: "<<allCells[1].right<<" , "<<allCells[1].down<<endl;
        cout<<"allcells[2] right and down walls: "<<allCells[2].right<<" , "<<allCells[2].down<<endl;
        cout<<"allcells[3] right and down walls: "<<allCells[3].right<<" , "<<allCells[3].down<<endl;
*/
        srand(time(NULL));
        int dir = rand()%4;//choose a random direction to move in (RDLU)
        int xr=rand()%mazeWidth;
        int yr=rand()%mazeHeight;
        currentCell= allCells[xr*mazeHeight+yr];

        //cout<<"Dir: "<<dir<<endl;
        if(dir==0){
            if(currentCell.pR==false){
                cell currentRight = allCells[currentCell.index+1];
                if(currentCell.right==true){
                    //if(canTravel(currentCell.xcoord,currentCell.ycoord,0)){
                        if(cycleCells.find(currentCell.index)!=cycleCells.find(currentRight.index)){
                            setWall(currentCell.xcoord,currentCell.ycoord,0,false);
                            cycleCells.setunion(currentCell.index,currentRight.index);
                            cout<<"Current: "<<cycleCells.find(currentCell.index)<<endl;
                            cout<<"CurrentUp: "<<cycleCells.find(currentRight.index)<<endl;
                            //currentCell=allCells[currentCell.index+1];
                            numTrees--;
                        }
                    //}
                }
            }
        }else if(dir==1){
            if(currentCell.pD==false){
                cell currentDown = allCells[currentCell.index+mazeHeight];
                if(currentCell.down==true){
                    //if(canTravel(currentCell.xcoord,currentCell.ycoord,1)){
                        if(cycleCells.find(currentCell.index)!=cycleCells.find(currentDown.index)){
                            setWall(currentCell.xcoord,currentCell.ycoord,1,false);
                            cycleCells.setunion(currentCell.index,currentDown.index);
                            cout<<"Current: "<<cycleCells.find(currentCell.index)<<endl;
                            cout<<"CurrentUp: "<<cycleCells.find(currentDown.index)<<endl;
                            //currentCell=allCells[currentCell.index+mazeHeight];
                            numTrees--;
                        }
                    //}
                }
            }
        }else if(dir==2){
            if(currentCell.pL==false){
                cell currentLeft = allCells[currentCell.index-1];
                if(currentLeft.right==true){
                    //if(canTravel(currentCell.xcoord,currentCell.ycoord,2)){
                        if(cycleCells.find(currentCell.index)!=cycleCells.find(currentLeft.index)){
                            setWall(currentLeft.xcoord,currentLeft.ycoord,0,false);
                            cycleCells.setunion(currentCell.index,currentLeft.index);
                            cout<<"Current: "<<cycleCells.find(currentCell.index)<<endl;
                            cout<<"CurrentUp: "<<cycleCells.find(currentLeft.index)<<endl;
                            //currentCell=allCells[currentCell.index-1];
                            numTrees--;
                        }
                    //}
                }
                
            }
        }else if(dir==3){
            if(currentCell.pU==false){
                cell currentUp = allCells[currentCell.index-mazeHeight];
                if(currentUp.down==true){
                    //if(canTravel(currentCell.xcoord,currentCell.ycoord,3)){
                        if(cycleCells.find(currentCell.index)!=cycleCells.find(currentUp.index)){
                            setWall(currentUp.xcoord,currentUp.ycoord,1,false);
                            cycleCells.setunion(currentCell.index,currentUp.index);
                            cout<<"Current: "<<cycleCells.find(currentCell.index)<<endl;
                            cout<<"CurrentUp: "<<cycleCells.find(currentUp.index)<<endl;
                            //currentCell=allCells[currentCell.index-mazeHeight];
                            numTrees--;
                        }
                    //}
                }
            }
        }
        cycleCells.printAllNodes();
        cout<<"NumTrees: "<<numTrees<<endl;
        cout<<"allcells[0] right and down walls: "<<allCells[0].right<<" , "<<allCells[0].down<<endl;
        cout<<"allcells[1] right and down walls: "<<allCells[1].right<<" , "<<allCells[1].down<<endl;
        cout<<"allcells[2] right and down walls: "<<allCells[2].right<<" , "<<allCells[2].down<<endl;
        cout<<"allcells[3] right and down walls: "<<allCells[3].right<<" , "<<allCells[3].down<<endl;
        sleep_until(system_clock::now() + seconds(1));
        
    }
}
bool SquareMaze::canTravel(int x,int y, int dir) const{
   cell currentCell = allCells[x*mazeHeight+y];
        if(dir==0){
            if(x==mazeWidth-1){
                return false;
            }
            if(currentCell.pR==false){
                if(currentCell.right==false){//if the right wall is not a perimeter and has a wall
                    cout<<"X: "<<x<<" , Y: "<<y<<endl;
                    cout<<"HasRight wall: "<<currentCell.right<<endl;
                    cout<<"Has right perimeter wall: "<<currentCell.pR<<endl;
                    return true;
                }
            }else{
                return false;
            }
        }else if(dir==1){
            if(y==mazeHeight-1){
                return false;
            }
            if(currentCell.pD==false){
                if(currentCell.down==false){//if the down wall is not a perimeter and has a wall
                    cout<<"X: "<<x<<" , Y: "<<y<<endl;
                    cout<<"HasDown wall: "<<currentCell.down<<endl;
                    cout<<"Has down perimeter wall: "<<currentCell.pD<<endl;
                    return true;
                }
            }else{
                return false;
            }
        }else if(dir==2){
             if(currentCell.pL==false){
                cell currentLeft = allCells[currentCell.index-1];
                if(currentLeft.right==false){//if the left wall is not a perimeter and has a wall
                    return true;
                }
            }else{
                return false;
            }
        }else if(dir==3){
            if(currentCell.pU==false){
                cell currentUp = allCells[currentCell.index-mazeHeight];
                if(currentUp.down==false){
                    return true;
                }
            }else{
                return false;
            }
        }
    return false;
}

PNG * SquareMaze::drawMaze() const{
    PNG *im=nullptr;
    return im;
}
PNG * SquareMaze::drawMazeWithSolution(){
    PNG *im=nullptr;
    return im;
}

void SquareMaze::setWall(int x,int y, int dir, bool exists){
    int index = x*mazeHeight+y;
    if(exists==false){
        if(dir==1){
            allCells[index].down=false;
        }else if(dir==0){
            allCells[index].right=false;
        }
    }else{
        if(dir==1){
            allCells[index].down=true;
        }else if(dir==0){
            allCells[index].right=true;
        }
    }
}
vector<int> SquareMaze::solveMaze(){
    vector<int> hi;
    return hi;
}