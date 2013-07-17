/*
 * aStar.cpp
 *
 *  Created on: May 29, 2013
 *      Author: cjgrady
 */

#include <cmath>
#include "aStar.h"

double AStar::heuristicRook(int x, int y)
{
   double c;
   double distance;

   distance = abs(x - dstX) + abs(y - dstY);
   c = (mat[y][x] + mat[dstY][dstX]) / 2.0;

   return distance * c;
}

double AStar::getCostRook(double cc, int x, int y)
{
   if (x >= 0 and y >= 0 and x < nCols and y < nRows)
      return cc + mat[y][x] + heuristicRook(x, y);
   else
      return -1.0;
}

void AStar::run(int srcX, int srcY)
{
   cout << "A" << endl;
   runRook(srcX, srcY);
   cout << "B" << endl;
   //h.reset();
   cout << "C" << endl;
}

void AStar::runRook(int srcX, int srcY)
{
   cout << "1" << endl;
   bool cont = true;
   cout << "2" << endl;
   Cell cell;

   cout << "3" << endl;
   // add cells connected to source
   addCellsRook(srcX, srcY, 0.0);

   cout << "4" << endl;
   if (srcX == dstX and srcY == dstY)
      cont = false;

   cout << "5" << endl;
   // while not stop condition
   while (cont and itemsLeft())
   {
      cout << "6" << endl;
      cell = getNextLCP();
      cout << "7" << endl;
      if (cell.x == dstX and cell.y == dstY)
         cont = false;
      cout << "8" << endl;
      addCellsRook(cell.x, cell.y, cell.cost);
      cout << "9" << endl;
   }
   cout << "10" << endl;
}

void AStar::addCellsRook(int x, int y, double cc)
{
   addCell(x-1, y, getCostRook(cc, x-1, y), LEFT);
   addCell(x+1, y, getCostRook(cc, x+1, y), RIGHT);
   addCell(x, y-1, getCostRook(cc, x, y-1), TOP);
   addCell(x, y+1, getCostRook(cc, x, y+1), BOTTOM);
}
