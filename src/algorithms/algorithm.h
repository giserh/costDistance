/*
 * algorithm.h
 *
 *  Created on: May 9, 2013
 *      Author: cjgrady
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include <string>
#include <vector>

#include "../heaps/GeoHeap.h"
#include "../heaps/GeoNode.h"

using namespace std;

const int TOP_LEFT = 1;
const int TOP = 2;
const int TOP_RIGHT = 3;
const int RIGHT = 4;
const int BOTTOM_RIGHT = 5;
const int BOTTOM = 6;
const int BOTTOM_LEFT = 7;
const int LEFT = 8;

struct AlgoStats
{
   int frontSize;
   int numCellsTouched;
   int maxFrontSize;
   int numSteps;
};

struct Cell
{
   int x;
   int y;
   double cost;
};

class Algorithm
{
   protected:
      AlgoStats stats;
      int dstX, dstY;
      GeoHeap<GeoNode> h;
      vector < vector <int> > mat;
      vector < vector <float> > conn, costs, bl;
      void addCell(int x, int y, double cc, int backLink);
      Cell getNextLCP();
      bool itemsLeft();
   public:
      int nRows, nCols, cellSize, noDataVal, xllCorner, yllCorner;
      AlgoStats getStatistics();
      void printMatrix();
      void printCosts();
      void printMetadata();
      void readAsciiGrid(char * fileName);
      void resetMatrices();
      void resetStatistics();
      void virtual run(int srcX, int srcY);
      void setConnectivity(string connectivity);
      void setDestination(int dX, int dY);
      void writeBackLinks(char * fileName);
      void writeCostLayer(char * fileName);
      virtual ~Algorithm();
};


#endif /* ALGORITHM_H_ */
