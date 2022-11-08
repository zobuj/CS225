/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas * output = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> pointsForTree;
    map<Point<3>,int> pointIndex;
    map<int,TileImage*> tiles;
    for(size_t i = 0;i<theTiles.size();i++){
        pointsForTree.push_back(convertToXYZ(theTiles[i].getAverageColor()));
        pointIndex[convertToXYZ(theTiles[i].getAverageColor())]=i;
        tiles[i]=&theTiles[i];
    }
    KDTree<3> searchTree = KDTree<3>(pointsForTree);
    for(int rows = 0;rows<theSource.getRows();rows++){
        for(int cols = 0;cols<theSource.getColumns();cols++){
            Point<3> replaceNode = searchTree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(rows,cols)));
            int pI = pointIndex[replaceNode];
            output->setTile(rows,cols,tiles[pI]);
        }
    }
    return output;
}

