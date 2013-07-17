/*
 * aStar.h
 *
 *  Created on: May 9, 2013
 *      Author: cjgrady
 */

#ifndef ASTAR_H_
#define ASTAR_H_

#include "algorithm.h"

class AStar : public Algorithm
{
   public:
      void virtual run(int srcX, int srcY);
   private:
      void addCellsRook(int x, int y, double cc);
      double heuristicRook(int x, int y);
      double getCostRook(double cc, int x, int y);
      void runRook(int srcX, int srcY);
};


#endif /* ASTAR_H_ */
