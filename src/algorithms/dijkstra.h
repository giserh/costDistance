/*
 * dijkstra.h
 *
 *  Created on: Jul 15, 2013
 *      Author: cjgrady
 */

#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include "algorithm.h"

const float SQRT_2_DIV_2 = 0.7071;

class Dijkstra : public Algorithm
{
   public:
      void init();
      void virtual run();
      void addSourceCellQueen(int x, int y);
      void addSourceCellRook(int x, int y);
      void addStopValue(double stopCost);
   private:
      void addCellsRook(int x, int y, double cc);
      void addCellsQueen(int x, int y, double cc);
      double getCostRook(double cc, int x, int y);
      double getCostQueen(double cc, int x, int y);
      double getCostRook(double cc, int x, int y, double fromCost);
      double getCostQueen(double cc, int x, int y, double fromCost);
      void runRook();
      void runQueen();
      int stopValue;
};




#endif /* DIJKSTRA_H_ */
