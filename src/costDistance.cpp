//============================================================================
// Name        : costDistance.cpp
// Author      : CJ Grady
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
//#include "algorithms/aStar.h"
#include "algorithms/dijkstra.h"
#include "indexStructures/liArray.h"

using namespace std;

void runDijkstra()
{
   AlgoStats stats;
   Dijkstra a;
   //a.readAsciiGrid("/home/cjgrady/t.asc");
   //a.readAsciiGrid("/home/cjgrady/ALT_Worldclim1.4_NA.asc");
   a.readAsciiGrid("/home/cjgrady/demo/lyr.asc");
   a.init();
   a.addSourceCellQueen(5, 5);
   a.addSourceCellQueen(150, 150);
   a.addSourceCellQueen(90, 140);
   a.addSourceCellQueen(190, 35);
   a.addSourceCellQueen(20, 170);
   a.addSourceCellQueen(100, 100);
   a.addSourceCellQueen(170, 180);
   a.addStopValue(150000.0);
   a.run();
   stats = a.getStatistics();
   cout << "Front size: " << stats.frontSize << endl;
   cout << "Num cells touched: " << stats.numCellsTouched << endl;
   cout << "Max front size: " << stats.maxFrontSize << endl;
   cout << "Number of steps: " << stats.numSteps << endl;
   //a.writeCostLayer("/home/cjgrady/dTestOut.asc");
   a.writeCostLayer("/home/cjgrady/demo/outLyr6.asc");
}
//
//void runAstarTests()
//{
//   AlgoStats stats;
//   AStar a;
//   a.readAsciiGrid("/home/cjgrady/t.asc");
//
//   for (int x=0; x < a.nCols; x++)
//      for (int y=0; y < a.nRows; y++)
//      {
//         cout << "a" << endl;
//         a.setDestination(x, y);
//         cout << "b" << endl;
//         a.resetStatistics();
//         cout << "c" << endl;
//         a.run(0, 0);
//         cout << "d" << endl;
//         stats = a.getStatistics();
//         cout << "e" << endl;
//         cout << "("<< x<<"," << y << "): "<< stats.maxFrontSize << ", "
//              << stats.numCellsTouched << ", " << stats.numSteps << endl;
//         cout << "f" << endl;
//         a.printCosts();
//         cout << "g" << endl;
//         a.resetMatrices();
//         cout << "h" << endl;
//      }
//}



void testLIArray()
{
   LIArray<int> i;


   int * b;
   b = new int(4);

   i.insert(1, b);
   int a = *i.get(1);
   cout << "Got: " << a << endl;
   i.rm(1);
   try
   {
      cout << "a" << endl;
      a = *i.get(1);
   }
   catch (exception &e)
   {
      cout << e.what() << endl;
   }

   cout << "b" << endl;
   cout << "Got (num 2): " << a << endl;
}

int main() {
   runDijkstra();
   //testLIArray();
   cout << "Success" << endl;
   return 0;
}
