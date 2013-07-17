/*
 * algorithm.cpp
 *
 *  Created on: May 9, 2013
 *      Author: cjgrady
 */

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>

#include "algorithm.h"

const float SQRT_2_DIV_2 = 0.7071;

AlgoStats Algorithm::getStatistics()
{
   return stats;
}

void Algorithm::resetMatrices()
{
   costs.clear();
   bl.clear();
   h.reset();
}

void Algorithm::resetStatistics()
{
   stats.frontSize = 0;
   stats.numCellsTouched = 0;
   stats.maxFrontSize = 0;
   stats.numSteps = 0;
}

Algorithm::~Algorithm()
{

}

void Algorithm::addCell(int x, int y, double cc, int backLink)
{
   if (x >= 0 and x < nCols and y >= 0 and y < nRows and costs[y][x] < 0.1)
   {
      cout << "Adding cell (" << x << ", " << y << ")  ";
      //cout << "x=" << x << endl;
      //cout << "y=" << y << endl;
      cout << " val=" << mat[y][x] << " ";
      cout << "cc=" << cc << endl;
      //cout << "bl=" << backLink << endl;
      h.push(GeoNode(nCols*y+x, cc, backLink));
      cout << "Pushed" << endl;
      //stats
      stats.frontSize++;
      cout << "stats1";
      //cout << "fs added" << endl;
      stats.numCellsTouched++;
      //cout << "Touched + 1" << endl;
      cout <<"2";
      if (stats.frontSize > stats.maxFrontSize)
         stats.maxFrontSize = stats.frontSize;
      //cout << "Done" << endl;
      cout << "3" << endl;
   }
   cout << "Done adding cell" << endl;
}

Cell Algorithm::getNextLCP()
{
   Cell c;
   GeoNode r;
   int x, y;

   r = h.pop();
   x = r.getIndex() % nCols;
   y = int(r.getIndex() / nRows);
   costs[y][x] = r.getValue();
   bl[y][x] = r.getBackLink();

   // Stats
   stats.numSteps++;
   stats.frontSize--;

   c.x = x;
   c.y = y;
   c.cost = r.getValue();
   return c;
}

bool Algorithm::itemsLeft()
{
   return not h.empty();
}

void Algorithm::printCosts()
{
   for (int y = 0; y < nRows; y++)
   {
      for (int x = 0; x < nCols; x++)
         cout << costs[y][x] << " ";
      cout << endl;
   }
}

void Algorithm::printMatrix()
{
   for (int y = 0; y < nRows; y++)
   {
      for (int x = 0; x < nCols; x++)
         cout << mat[y][x] << " ";
      cout << endl;
   }
}

void Algorithm::printMetadata()
{
   cout << "nRows " << nRows << endl;
   cout << "nCols " << nCols << endl;
   cout << "cellsize " << cellSize << endl;
   cout << "xllcorner " << xllCorner << endl;
   cout << "yllcorner " << yllCorner << endl;
   cout << "NoData " << noDataVal << endl;
}

void Algorithm::readAsciiGrid(char * fileName)
{
   string line, item, item2;
   stringstream ss;
   ifstream inFile;

   inFile.open(fileName);

   if (inFile.is_open())
   {
      while (inFile.good())
      {
         getline(inFile, line);
         ss << line;
         ss >> item;
         ss >> item2;

         if (item == "nrows")
            nRows = atoi(item2.c_str());
         else if (item == "ncols")
            nCols = atoi(item2.c_str());
         else if (item == "cellsize")
            cellSize = atoi(item2.c_str());
         else if (item == "xllcorner")
            xllCorner = atoi(item2.c_str());
         else if (item == "yllcorner")
            yllCorner = atoi(item2.c_str());
         else if (item == "NODATA_value")
            noDataVal = atoi(item2.c_str());
         else
         {
            mat.resize( nRows, vector <int>(nCols, 0));
            costs.resize( nRows, vector <float>(nCols, -9999.0));
            bl.resize( nRows, vector <float>(nCols, -9999.0));
            // read in data

            mat[0][0] = atoi(item.c_str());
            mat[0][1] = atoi(item2.c_str());

            for (int x= 2; x < nCols; x++)
               ss >> mat[0][x];
            for (int y=1; y < nRows; y++)
               for (int x=0; x < nCols; x++)
                  inFile >> mat[y][x];
         }

         // Reset stringsteam
         ss.str("");
         ss.clear();
      }

      inFile.close();
   }
   else
   {
      cout << "Could not open file: " << fileName << endl;
   }

}

// Note: virtual
void Algorithm::run(int srcX, int srcY)
{

}

void Algorithm::setConnectivity(string connectivity)
{
   if (connectivity == "rook")
   {
      conn.resize(3, vector <float>(3, 0.0));
      conn[0][1] = 1.0;
      conn[1][0] = 1.0;
      conn[1][2] = 1.0;
      conn[2][1] = 1.0;
   }
   else if (connectivity == "queen")
   {
      conn.resize(3, vector <float>(3, 0.0));
      conn[0][0] = SQRT_2_DIV_2;
      conn[0][1] = 1.0;
      conn[0][2] = SQRT_2_DIV_2;
      conn[1][0] = 1.0;
      conn[1][2] = 1.0;
      conn[2][0] = SQRT_2_DIV_2;
      conn[2][1] = 1.0;
      conn[2][2] = SQRT_2_DIV_2;
   }
}

void Algorithm::setDestination(int dX, int dY)
{
   dstX = dX;
   dstY = dY;
}

void Algorithm::writeBackLinks(char * fileName)
{
   ofstream out;
   out.open(fileName);

   out << "nrows   " << nRows << endl;
   out << "ncols   " << nCols << endl;
   out << "xllcorner   0.0" << endl;
   out << "yllcorner   0.0" << endl;
   out << "cellsize   " << cellSize << endl;
   out << "NODATA_value   " << -9999.0 << endl;

   // Back link layer rows
   for (int y = 0; y < nRows; y++)
   {
      for (int x = 0; x < nCols; x++)
         out << bl[y][x] << " ";
      out << endl;
   }

   out.close();
}

void Algorithm::writeCostLayer(char * fileName)
{
   ofstream out;
   out.open(fileName);

   out << "nrows   " << nRows << endl;
   out << "ncols   " << nCols << endl;
   out << "xllcorner  " << xllCorner << endl;
   out << "yllcorner  " << xllCorner << endl;
   out << "cellsize   " << cellSize << endl;
   out << "NODATA_value   " << -9999.0 << endl;

   // cost layer rows
   for (int y = 0; y < nRows; y++)
   {
      for (int x = 0; x < nCols; x++)
         out << costs[y][x] << " ";
      out << endl;
   }

   out.close();
}

