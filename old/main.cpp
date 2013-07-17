/*
 * main.cpp
 *
 *  Created on: Oct 18, 2012
 *      Author: cjgrady
 */

#include <iostream>
#include <fstream>
#include <math.h>

#include "GeoHeap.h"
#include "GeoNode.h"
//#include "FibHeap.h"
//#include "geoHash.h"

using namespace std;

double getCost(double cc, int val1, int val2, bool diagonal)
{
   double c = 0.0;
   if (diagonal)
      c = (sqrt(2) * (val1 + val2)) / 2.0;
   else
      c = (val1 + val2) / 2.0;
   return cc + c;
}

int main()
{
   const int TOP_LEFT = 1;
   const int TOP = 2;
   const int TOP_RIGHT = 3;
   const int RIGHT = 4;
   const int BOTTOM_RIGHT = 5;
   const int BOTTOM = 6;
   const int BOTTOM_LEFT = 7;
   const int LEFT = 8;

   const int height = 500;
   const int width = 500;
   int rst[height][width] = {{0}};
   double cstRst[height][width] = {{-1.0}};
   int bl[height][width] = {{0}};
   int srcX = 3;
   int srcY = 3;
   double cc = 0.0;

   GeoHeap<GeoNode> h;
   GeoNode r;

   ifstream file;
   file.open("/home/cjgrady/randRst500x500.asc");
   for (int i = 0; i < height; i++)
      for (int j = 0; j < width; j++)
         file >> rst[i][j];

   file.close();

   // push initial values
   if (srcX > 0 and srcY > 0)
      h.push(GeoNode(
               width*(srcY-1)+srcX-1,
               getCost(cc, rst[srcY][srcX], rst[srcY-1][srcX-1], true),
               TOP_LEFT)
            );

   if (srcY > 0)
      h.push(GeoNode(
               width*(srcY-1)+srcX,
               getCost(cc, rst[srcY][srcX], rst[srcY-1][srcX], false),
               TOP)
            );

   if (srcX < width-1 and srcY > 0)
      h.push(GeoNode(
               width*(srcY-1)+srcX+1,
               getCost(cc, rst[srcY][srcX], rst[srcY-1][srcX+1], true),
               TOP_RIGHT)
            );

   if (srcX > 0)
      h.push(GeoNode(
               width*(srcY)+srcX-1,
               getCost(cc, rst[srcY][srcX], rst[srcY][srcX-1], true),
               LEFT)
            );

   if (srcX < width-1)
      h.push(GeoNode(
               width*(srcY)+srcX+1,
               getCost(cc, rst[srcY][srcX], rst[srcY][srcX+1], true),
               RIGHT)
            );

   if (srcX > 0 and srcY < height-1)
      h.push(GeoNode(
               width*(srcY+1)+srcX-1,
               getCost(cc, rst[srcY][srcX], rst[srcY+1][srcX-1], true),
               BOTTOM_LEFT)
            );

   if (srcY < height-1)
      h.push(GeoNode(
               width*(srcY+1)+srcX,
               getCost(cc, rst[srcY][srcX], rst[srcY+1][srcX], false),
               BOTTOM)
            );

   if (srcX < width-1 and srcY < height-1)
      h.push(GeoNode(
               width*(srcY+1)+srcX+1,
               getCost(cc, rst[srcY][srcX], rst[srcY+1][srcX+1], true),
               BOTTOM_RIGHT)
            );

   int numLeft = height * width;
   int x, y;

   while (numLeft > 0)
   {
      cout << "Num left: " << numLeft << endl;
      r = h.pop();
      x = r.getIndex() % height;
      y = int(r.getIndex() / height);
      cstRst[y][x] = r.getValue();
      bl[y][x] = r.getBackLink();
      cc = r.getValue();

      if (x > 0 and y > 0 and cstRst[y-1][x-1] < 0.1)
         h.push(GeoNode(
                  width*(y-1)+x-1,
                  getCost(cc, rst[y][x], rst[y-1][x-1], true),
                  TOP_LEFT)
               );

      if (y > 0 and cstRst[y-1][x] < 0.1)
         h.push(GeoNode(
                  width*(y-1)+x,
                  getCost(cc, rst[y][x], rst[y-1][x], false),
                  TOP)
               );

      if (x < width-1 and y > 0 and cstRst[y-1][x+1] < 0.1)
         h.push(GeoNode(
                  width*(y-1)+x+1,
                  getCost(cc, rst[y][x], rst[y-1][x+1], true),
                  TOP_RIGHT)
               );

      if (x > 0 and cstRst[y][x-1] < 0.1)
         h.push(GeoNode(
                  width*(y)+x-1,
                  getCost(cc, rst[y][x], rst[y][x-1], true),
                  LEFT)
               );

      if (x < width-1 and cstRst[y][x+1] < 0.1)
         h.push(GeoNode(
                  width*(y)+x+1,
                  getCost(cc, rst[y][x], rst[y][x+1], true),
                  RIGHT)
               );

      if (x > 0 and y < height-1 and cstRst[y+1][x-1] < 0.1)
         h.push(GeoNode(
                  width*(y+1)+x-1,
                  getCost(cc, rst[y][x], rst[y+1][x-1], true),
                  BOTTOM_LEFT)
               );

      if (y < height-1 and cstRst[y+1][x] < 0.1)
         h.push(GeoNode(
                  width*(y+1)+x,
                  getCost(cc, rst[y][x], rst[y+1][x], false),
                  BOTTOM)
               );

      if (x < width-1 and y < height-1 and cstRst[y+1][x+1] < 0.1)
         h.push(GeoNode(
                  width*(y+1)+x+1,
                  getCost(cc, rst[y][x], rst[y+1][x+1], true),
                  BOTTOM_RIGHT)
               );
      numLeft--;
   }

   cstRst[srcY][srcX] = 0.0;
   bl[srcY][srcX] = 0;

   // view raster
   for (int i = 0; i < height; i++)
   {
      for (int j = 0; j < width; j++)
      {
         cout << cstRst[i][j] << " ";
      }
      cout << endl;
   }

   cout << endl << endl << endl;
   // view backlinks
   for (int i = 0; i < height; i++)
   {
      for (int j = 0; j < width; j++)
      {
         cout << bl[i][j] << " ";
      }
      cout << endl;
   }



   return 0;
}


