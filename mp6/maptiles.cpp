/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    /**
     * @todo Implement this function!
     */
	MosaicCanvas * haha = new MosaicCanvas(theSource.getRows(),theSource.getColumns());
	vector<Point<3>> points;
	map <Point<3>,TileImage> themap;
	//first we made a tree of theTiles
	for (unsigned long i = 0; i < theTiles.size(); i ++){
		RGBAPixel color = theTiles[i].getAverageColor();
		Point<3> lala (color.red,color.green,color.blue);
		points.push_back(lala);
	//and a map
		themap[lala] = theTiles[i];	
	}
	KDTree<3> tree(points);
	//then we try to find the nearest image
	for (int i = 0; i < theSource.getRows();i++){
		for( int j = 0; j < theSource.getColumns(); j++){
			RGBAPixel need = theSource.getRegionColor(i ,j);
			Point<3> target (need.red,need.green,need.blue);
			Point<3> result = tree.findNearestNeighbor(target);
			//set the image
			haha->setTile(i,j,themap[result]);
	}
}
	return haha;
}
