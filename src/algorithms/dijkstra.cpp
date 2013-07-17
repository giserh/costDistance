/*
 * dijkstra.cpp
 *
 *  Created on: Jul 15, 2013
 *      Author: cjgrady
 */

#include <cmath>
#include "dijkstra.h"

//   public:
//      void virtual run();

void Dijkstra::addSourceCellRook(int x, int y)
{
   addCellsRook(x, y, 0.0);
}

void Dijkstra::addSourceCellQueen(int x, int y)
{
   addCellsQueen(x, y, 0.0);
}

void Dijkstra::addStopValue(double stopCost)
{
   stopValue = stopCost;
}

double Dijkstra::getCostRook(double cc, int x, int y)
{
   if (x >= 0 and y >= 0 and x < nCols and y < nRows)
      return cc + mat[y][x] * cellSize / 2.0;
   else
      return -1.0;
}

double Dijkstra::getCostRook(double cc, int x, int y, double fromCost)
{
   if (x >= 0 and y >= 0 and x < nCols and y < nRows)
      return cc + (mat[y][x] + fromCost) * cellSize / 2.0;
   else
      return -1.0;
}

double Dijkstra::getCostQueen(double cc, int x, int y)
{
   if (x >= 0 and y >= 0 and x < nCols and y < nRows)
      return cc + mat[y][x] * cellSize * SQRT_2_DIV_2;
   else
      return -1.0;
}

double Dijkstra::getCostQueen(double cc, int x, int y, double fromCost)
{
   if (x >= 0 and y >= 0 and x < nCols and y < nRows)
      return cc + (mat[y][x] + fromCost) * cellSize * SQRT_2_DIV_2 / 2.0;
   else
      return -1.0;
}

void Dijkstra::init()
{
   h.setNumCells(nCols*nRows);
}

void Dijkstra::run()
{
   cout << "Run Dijkstra" << endl;
   //runRook();
   runQueen();
}

void Dijkstra::runRook()
{
   cout << "Run Rook" << endl;

   Cell cell;
   bool cont = true;

   while (cont and itemsLeft())
   {
      cell = getNextLCP();
      if (stopValue > 0 and stopValue < cell.cost)
      {
         cont = false;
         cout << "Reached stop value: " << stopValue << " < " << cell.cost << endl;
      }
      addCellsRook(cell.x, cell.y, cell.cost);
   }
}

void Dijkstra::runQueen()
{
   cout << "Run Queen" << endl;

   Cell cell;
   bool cont = true;

   while (cont and itemsLeft())
   {
      cell = getNextLCP();
      if (stopValue > 0 and stopValue < cell.cost)
      {
         cont = false;
         cout << "Reached stop value: " << stopValue << " < " << cell.cost << endl;
      }

      addCellsQueen(cell.x, cell.y, cell.cost);
   }
}
void Dijkstra::addCellsRook(int x, int y, double cc)
{
   cout << "Add cells rook" << endl;
   double fromCost = mat[y][x];
   addCell(x-1, y, getCostRook(cc, x-1, y, fromCost), LEFT);
   addCell(x+1, y, getCostRook(cc, x+1, y, fromCost), RIGHT);
   addCell(x, y-1, getCostRook(cc, x, y-1, fromCost), TOP);
   addCell(x, y+1, getCostRook(cc, x, y+1, fromCost), BOTTOM);
}

void Dijkstra::addCellsQueen(int x, int y, double cc)
{
   double fromCost = mat[y][x];
   addCell(x-1, y-1, getCostQueen(cc, x-1, y-1, fromCost), TOP_LEFT);
   addCell(x, y-1, getCostRook(cc, x, y-1, fromCost), TOP);
   addCell(x+1, y-1, getCostQueen(cc, x+1, y-1, fromCost), TOP_RIGHT);
   addCell(x-1, y, getCostQueen(cc, x-1, y, fromCost), LEFT);
   addCell(x+1, y, getCostRook(cc, x+1, y, fromCost), RIGHT);
   addCell(x-1, y+1, getCostQueen(cc, x-1, y+1, fromCost), BOTTOM_LEFT);
   addCell(x, y+1, getCostRook(cc, x, y+1, fromCost), BOTTOM);
   addCell(x+1, y+1, getCostQueen(cc, x+1, y+1, fromCost), BOTTOM_RIGHT);
}



