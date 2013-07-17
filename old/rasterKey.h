/*
 * rasterKey.h
 *
 *  Created on: Oct 22, 2012
 *      Author: cjgrady
 */

#ifndef RASTERKEY_H_
#define RASTERKEY_H_

#include <iostream>
#include <ostream>

using namespace std;

class RasterKey
{
private:
   int row;
   int col;
   double value;
   int backLink;

public:
   RasterKey();
   RasterKey(int r, int c, double v, int b);

   // accessors
   int getBackLink();
   int getRow();
   int getCol();
   double getValue();

   // modifiers
   void setBackLink(int bl);
   void setCol(int c);
   void setRow(int r);
   void setValue(double v);

   // overload operators
   friend ostream& operator<<(ostream& os, RasterKey& n);

   bool operator < (RasterKey &);
   bool operator > (RasterKey &);
   bool operator <= (RasterKey &);
   bool operator >= (RasterKey &);

   // other
   int getLinearIndex();
};

RasterKey::RasterKey()
{
   row = 0;
   col = 0;
   value = 0.0;
   backLink = 0;
}

RasterKey::RasterKey(int r, int c, double v, int b)
{
   row = r;
   col = c;
   value = v;
   backLink = b;
}

void RasterKey::setBackLink(int bl)
{
   backLink = bl;
}

void RasterKey::setCol(int c)
{
   col = c;
}

void RasterKey::setRow(int r)
{
   row = r;
}

void RasterKey::setValue(double v)
{
   value = v;
}

int RasterKey::getCol()
{
   return col;
}

int RasterKey::getRow()
{
   return row;
}

double RasterKey::getValue()
{
   return value;
}

int RasterKey::getBackLink()
{
   return backLink;
}

ostream& operator << (ostream &os, RasterKey & rk)
{
   os << "Node: row = "<< rk.getRow()
      << "; col = "<< rk.getCol()
      << "; value = " << rk.getValue()
      << "; backLink = " << rk.getBackLink();
   return os;
}

bool RasterKey::operator < (RasterKey& right)
{
   return value < right.getValue();
}

bool RasterKey::operator <= (RasterKey& right)
{
   return value <= right.getValue();
}

bool RasterKey::operator > (RasterKey& right)
{
   return value > right.getValue();
}

bool RasterKey::operator >= (RasterKey& right)
{
   return value >= right.getValue();
}

int RasterKey::getLinearIndex()
{
   return row*col + col;
}

#endif /* RASTERKEY_H_ */
