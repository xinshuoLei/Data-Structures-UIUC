/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

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
    MosaicCanvas* mosaic = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    std::map<Point<3>, int> map;
    std::vector<Point<3>> vector;
    for (size_t i = 0; i < theTiles.size(); i++) {
        LUVAPixel color = theTiles[i].TileImage::getAverageColor();
        Point<3> point = Point<3>(color.l, color.u, color.v);
        map[point] = i;
        vector.push_back(point);
    }
    KDTree<3> tree(vector);
    for (int i = 0; i < theSource.getRows(); i++) {
        for (int j = 0; j < theSource.getColumns(); j++) {
            LUVAPixel region_color = theSource.getRegionColor(i, j);
            Point<3> region_point(region_color.l, region_color.u, region_color.v);
            Point<3> nearest = tree.findNearestNeighbor(region_point);
            mosaic->setTile(i, j, &theTiles[map[nearest]]);
        }
    }   
    return mosaic;
}

