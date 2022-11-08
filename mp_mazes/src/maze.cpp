#include "maze.h"
#include <iostream>
#include <queue>
#include <chrono>
#include <thread>
#include <algorithm>
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds
using namespace std;
SquareMaze::SquareMaze(){
    mazeWidth=0;
    mazeHeight=0;
    mazeSize=0;
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

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if(dir==1){
        allCells[y*mazeHeight+x].down=exists;
    }else if(dir==0){
        allCells[y*mazeHeight+x].right=exists;
    }
}
std::vector<int> SquareMaze::solveMaze(){
    /*
    Things we need to store:
    - Maze Path (found using queue)
    - Distance from the origin for each cells
    - Visited Cells
    - Origin Cell
    */
    std::vector<unsigned int> mazePath;//will be filled with the directions needed to take in order to reach the destination
    std::vector<int> distanceToOrigin;
    std::vector<bool> visitedCells;
    std::queue<int> sol;
    int originCellIdx = 0;
    for(int i  = 0;i<mazeSize;i++){
        visitedCells.push_back(false);
        distanceToOrigin.push_back(0);
        mazePath.push_back(0);
    }
    sol.push(originCellIdx);
    visitedCells[0]=true;
    while(sol.empty()==false){
        int currentCellidx = sol.front();
        //cout<<currentCellidx<<" ";
        //check if we can travel right
        if(canTravel(allCells[currentCellidx].ycoord,allCells[currentCellidx].xcoord, 0)){
            int rightCellIndex=currentCellidx+1;
            if(visitedCells[rightCellIndex]==false){//check if the cell is not visited yet
                sol.push(rightCellIndex);
                //cout<<rightCellIndex<< " ";
                distanceToOrigin[rightCellIndex]=distanceToOrigin[currentCellidx]+1;
                mazePath[rightCellIndex]=currentCellidx;
                visitedCells[rightCellIndex]=true;
            }
        }
        //cout<<"TEST"<<endl;
        //check if we can travel down
        if(canTravel(allCells[currentCellidx].ycoord,allCells[currentCellidx].xcoord,1)){
            int downCellIndex = currentCellidx+mazeWidth;
            if(visitedCells[downCellIndex]==false){
                sol.push(downCellIndex);
                //cout<<downCellIndex<< " ";
                distanceToOrigin[downCellIndex]=distanceToOrigin[currentCellidx]+1;
                mazePath[downCellIndex]=currentCellidx;
                visitedCells[downCellIndex]=true;
            }
        }
        //cout<<"TEST"<<endl;
        //check if we can travel left
        if(canTravel(allCells[currentCellidx].ycoord,allCells[currentCellidx].xcoord,2)){
            int leftCellIndex = currentCellidx-1;
            if(visitedCells[leftCellIndex]==false){
                sol.push(leftCellIndex);
                //cout<<leftCellIndex<< " ";
                distanceToOrigin[leftCellIndex]=distanceToOrigin[currentCellidx]+1;
                mazePath[leftCellIndex]=currentCellidx;
                visitedCells[leftCellIndex]=true;
            }
        }
        //cout<<"TEST"<<endl;
        //check if we can travel up
        if(canTravel(allCells[currentCellidx].ycoord,allCells[currentCellidx].xcoord,3)){
            int upCellIndex = currentCellidx-mazeWidth;
            if(visitedCells[upCellIndex]==false){
                sol.push(upCellIndex);
                //cout<<upCellIndex<< " ";
                distanceToOrigin[upCellIndex]=distanceToOrigin[currentCellidx]+1;
                mazePath[upCellIndex]=currentCellidx;
                visitedCells[upCellIndex]=true;
            }
        }
        //cout<<"TEST"<<endl;
        //cout<<endl;
        sol.pop();
    }
    /*
    for(int j = 0;j<mazeWidth;j++){
        for(int k = 0;k<mazeHeight;k++){
            cout<<mazePath[j*mazeHeight+k]<<" ";
        }
        cout<<endl;
        

    }*/
    
    int greatestBottomIdx = 0;
    int currentLargestDistance = distanceToOrigin[(mazeWidth-1)*mazeHeight];
    
    for(int y = 0;y<mazeHeight;y++){
        if(distanceToOrigin[(mazeWidth-1)*mazeHeight+y]>currentLargestDistance){
            currentLargestDistance=distanceToOrigin[(mazeWidth-1)*mazeHeight+y];
            greatestBottomIdx=y;
        }
    }
    //cout<<"Current Largest Distance: "<<currentLargestDistance<<endl;
    //cout<<"Current Largest Distance Index: "<<greatestBottomIdx<<endl;

    /*unsigned int counter=0;
    for(size_t s = 0;s<mazePath.size();s++){
        cout<<"Index: "<<counter<<" -> "<<"Value: "<<mazePath[counter]<<endl;
        signed int result = counter-mazePath[counter];
        
        cout<<"Index-Value: "<<result<<endl;
        
        counter++;
    }*/
    vector<int> finalVector;
    
    int result=(mazeWidth-1)*mazeHeight+greatestBottomIdx;

    while(result!=0){
        
        signed int diff = result-mazePath[result];
        if(diff==1){
            finalVector.push_back(0);
        }
        else if(diff==-1){
            finalVector.push_back(2);
        }
        else if(diff==-mazeWidth){
            finalVector.push_back(3);
        }
        else if(diff==mazeWidth){
            finalVector.push_back(1);
        }
        result=mazePath[result];
        
        //cout<<result<<endl;
    }
    
    std::reverse(finalVector.begin(),finalVector.end());
    /*for(size_t p=0;p<finalVector.size();p++){
        cout<<finalVector[p]<<endl;
    }*/
    return finalVector;
}
PNG * SquareMaze::drawMaze()const{
    PNG * out = new PNG(mazeWidth*10+1,mazeHeight*10+1);
    unsigned int outWidth =out->width();
    unsigned int outHeight =out->height();

    for(unsigned int i = 0;i<outWidth;i++){
        for(unsigned int j=0;j<outHeight;j++){
            if((j==0||j==outWidth-1||i==0||i==outHeight-1)&&(!((i<=9 && i>=1)&&j==0))){
                //print black
                out->getPixel(i,j).h=0;
                out->getPixel(i,j).l=0;
                out->getPixel(i,j).s=0;
                out->getPixel(i,j).a=1;
            }
        }
    }
    for(int s =0;s<mazeWidth;s++){
        for(int t=0;t<mazeHeight;t++){
            if(allCells[t*mazeWidth+s].right==true){
                for(int k = 0;k<11;k++){
                    out->getPixel((s+1)*10,t*10+k).h=0;
                    out->getPixel((s+1)*10,t*10+k).l=0;
                    out->getPixel((s+1)*10,t*10+k).s=0;
                    out->getPixel((s+1)*10,t*10+k).a=1;

                }
            }
            if(allCells[t*mazeWidth+s].down==true){
                for(int u = 0;u<11;u++){
                    out->getPixel(s * 10 + u,(t + 1) * 10).h=0;
                    out->getPixel(s * 10 + u,(t + 1) * 10).l=0;
                    out->getPixel(s * 10 + u,(t + 1) * 10).s=0;
                    out->getPixel(s * 10 + u,(t + 1) * 10).a=1;

                }
            }
        }
    }
	return out;
}

PNG * SquareMaze::drawMazeWithSolution(){
    PNG * final = drawMaze();
    vector<int> solutionPath=solveMaze();
    final->getPixel(5,5).h=0;
    final->getPixel(5,5).s=1;
    final->getPixel(5,5).l=0.5;
    final->getPixel(5,5).a=1;
    
    
    int curPixX=5;
    int curPixY=5;
    for(size_t i=0;i<solutionPath.size();i++){
        
        if(solutionPath[i]==0){
            //right
            
            for(int x=0;x<11;x++){
                final->getPixel(curPixX+x,curPixY).h=0;
                final->getPixel(curPixX+x,curPixY).s=1;
                final->getPixel(curPixX+x,curPixY).l=0.5;
                final->getPixel(curPixX+x,curPixY).a=1;
            }
            curPixX+=10;
        }
        if(solutionPath[i]==1){
            //down
            
            for(int x=0;x<11;x++){
                final->getPixel(curPixX,curPixY+x).h=0;
                final->getPixel(curPixX,curPixY+x).s=1;
                final->getPixel(curPixX,curPixY+x).l=0.5;
                final->getPixel(curPixX,curPixY+x).a=1;
            }
            curPixY+=10;
        }
        if(solutionPath[i]==2){
            //left
            
            for(int x=0;x<11;x++){
                final->getPixel(curPixX-x,curPixY).h=0;
                final->getPixel(curPixX-x,curPixY).s=1;
                final->getPixel(curPixX-x,curPixY).l=0.5;
                final->getPixel(curPixX-x,curPixY).a=1;
            }
            curPixX-=10;
        }
        if(solutionPath[i]==3){
            //up
            
            for(int x=0;x<11;x++){
                final->getPixel(curPixX,curPixY-x).h=0;
                final->getPixel(curPixX,curPixY-x).s=1;
                final->getPixel(curPixX,curPixY-x).l=0.5;
                final->getPixel(curPixX,curPixY-x).a=1;
            }
            curPixY-=10;
        }
    }
    //cout<<curPixX<<" "<<curPixY<<endl;
    /*final->getPixel(curPixX+5,curPixY+5).h=0;
    final->getPixel(curPixX+5,curPixY+5).s=1;
    final->getPixel(curPixX+5,curPixY+5).l=0.5;
    final->getPixel(curPixX+5,curPixY+5).a=1;
    final->getPixel(curPixX+4,curPixY+5).h=1;
    final->getPixel(curPixX+4,curPixY+5).s=1;
    final->getPixel(curPixX+4,curPixY+5).l=1;
    final->getPixel(curPixX+4,curPixY+5).a=1;*/

    int finalCurPixX=curPixX+4;
    int finalCurPixY=curPixY+5;
    for(int w = 0;w<9;w++){
        final->getPixel(finalCurPixX-w,finalCurPixY).h=1;
        final->getPixel(finalCurPixX-w,finalCurPixY).s=1;
        final->getPixel(finalCurPixX-w,finalCurPixY).l=1;
        final->getPixel(finalCurPixX-w,finalCurPixY).a=1;
    }

    return final;
}