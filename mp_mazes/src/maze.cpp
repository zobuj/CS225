#include "maze.h"
#include <iostream>

using namespace std;
SquareMaze::SquareMaze(){

}
bool SquareMaze::canTravel(int x, int y, int dir) const {
	// check right
	if (dir == 0) {
		if (x >= mazeWidth - 1) return false;
		return !allCells[x + y * mazeWidth].rightWall;
	}
	// check dowm
	else if (dir == 1) {
		if (y >= mazeHeight - 1) return false;
		return !allCells[x + y * mazeWidth].downWall;
	}
	// check left
	else if (dir == 2) {
		if (x <= 0) return false;
		return !allCells[x  - 1 + y * mazeWidth].rightWall;
	}
	// check up
	else if (dir == 3) {
		if (y <= 0) return false;
		return !allCells[x + (y - 1) * mazeWidth].downWall;
	}
	else return false;
}
PNG * SquareMaze::drawMaze()const{
    PNG * result = new PNG(mazeWidth * 10 + 1, mazeHeight * 10 + 1);
	// Draw black lines if there are walls/edges
	for (int x = 0; x < mazeWidth; x++) {
		for (int y = 0; y < mazeHeight; y++) {
			if (y == 0) {  // If up side is edge, paint it black
				for (unsigned p = 0; p < 10; p++) {
					if ((x*10+p < 1) || (x*10+p > 9)) {
						HSLAPixel & cur_pixel = result->getPixel(x*10+p, 0);
						cur_pixel.l = 0;
					}
				}
			}
			if (x == 0) {  // If left side is edge, paint it black
				for (unsigned p = 0; p < 10; p++) {
					HSLAPixel & cur_pixel = result->getPixel(0, y*10+p);
					cur_pixel.l = 0;
				}
			}
			if (!canTravel(x, y, 0)) {  // If right side is wall, paint it black
				for (unsigned p = 0; p <= 10; p++) {
					HSLAPixel & cur_pixel = result->getPixel((x+1)*10, y*10+p);
					cur_pixel.l = 0;
				}
			}
			if (!canTravel(x, y, 1)) {  // If down side is wall, paint it black
				for (unsigned p = 0; p <= 10; p++) {
					HSLAPixel & cur_pixel = result->getPixel(x*10+p, (y+1)*10);
					cur_pixel.l = 0;
				}
			}
		}
	}
	return result;
}
PNG * SquareMaze::drawMazeWithSolution(){
    PNG * im = nullptr;
    return im;
}
void SquareMaze::makeMaze(int width, int height){
    mazeHeight = height;
    mazeWidth = width;
    DisjointSets cycleCells;
    cycleCells.addelements(width*height);
    for(int w  = 0;w<mazeWidth;w++){
        for(int h = 0;h<mazeHeight;h++){
            Cell c;
            c.rightWall=true;
            c.downWall=true;
            c.xcoord = w;
            c.ycoord = h;
            c.index=w*mazeHeight+h;
            allCells.push_back(c);
            //cout<<c.index<<" ";
        }
        //cout<<endl;
    }
    
    int numTrees = cycleCells.getNumTrees();
    Cell currentCell;
    while(numTrees>1){
        srand(time(NULL));
        int xr = rand()%mazeWidth;
        int yr = rand()%mazeHeight;
        int dir = rand()%2;
        currentCell = allCells[xr*mazeHeight+yr];
        if(dir==0){
            if(yr<(mazeHeight-1)){
                 if(cycleCells.find(currentCell.index)!=cycleCells.find(currentCell.index+1)){
                    //currentCell.rightWall=false;
                    setWall(currentCell.xcoord,currentCell.ycoord,0,false);
                    cycleCells.setunion(currentCell.index,currentCell.index+1);
                    numTrees--;
                 }
            }
        }else if(dir==1){
            if(xr<(mazeWidth-1)){
                if(cycleCells.find(currentCell.index)!=cycleCells.find(currentCell.index+mazeHeight)){
                    //currentCell.downWall=false;
                    setWall(currentCell.xcoord,currentCell.ycoord,1,false);
                    cycleCells.setunion(currentCell.index,currentCell.index+mazeHeight);
                    numTrees--;
                 }
            }
        }
        //cycleCells.printAllNodes();
       /* cout<<"NumTrees: "<<numTrees<<endl;
        cout<<"allcells[0] right and down walls: "<<allCells[0].rightWall<<" , "<<allCells[0].downWall<<endl;
        cout<<"allcells[1] right and down walls: "<<allCells[1].rightWall<<" , "<<allCells[1].downWall<<endl;
        cout<<"allcells[2] right and down walls: "<<allCells[2].rightWall<<" , "<<allCells[2].downWall<<endl;
        cout<<"allcells[3] right and down walls: "<<allCells[3].rightWall<<" , "<<allCells[3].downWall<<endl;*/
    }
}
void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if(dir==0){
        allCells[x*mazeHeight+y].rightWall=exists;
    }else if(dir==1){
        allCells[x*mazeHeight+y].downWall=exists;
    }
}
std::vector<int> SquareMaze::solveMaze(){
    std::vector<int> vec;
    return vec;
}