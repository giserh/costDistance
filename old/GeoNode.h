/*
 * GeoNode.h
 *
 *  Created on: Nov 7, 2012
 *      Author: cjgrady
 */

#ifndef GEONODE_H_
#define GEONODE_H_

#include <iostream>
#include <ostream>

using namespace std;

class GeoNode
{
private:
   int index;
   double value;
   int backLink;

public:
   GeoNode();
   GeoNode(int idx, double v, int b);

   // accessors
   int getBackLink();
   int getIndex();
   double getValue();

   // modifiers
   void setBackLink(int bl);
   void setIndex(int i);
   void setValue(double v);

   // overload operators
   friend ostream& operator<<(ostream& os, GeoNode& n);

   bool operator < (GeoNode &);
   bool operator > (GeoNode &);
   bool operator <= (GeoNode &);
   bool operator >= (GeoNode &);

};

GeoNode::GeoNode()
{
   index = -1;
   value = 0.0;
   backLink = 0;
}

GeoNode::GeoNode(int i, double v, int b)
{
   index = i;
   value = v;
   backLink = b;
}

void GeoNode::setBackLink(int bl)
{
   backLink = bl;
}

void GeoNode::setIndex(int i)
{
   index = i;
}

void GeoNode::setValue(double v)
{
   value = v;
}

int GeoNode::getIndex()
{
   return index;
}

double GeoNode::getValue()
{
   return value;
}

int GeoNode::getBackLink()
{
   return backLink;
}

ostream& operator << (ostream &os, GeoNode & rk)
{
   os << "Node: index = "<< rk.getIndex()
      << "; value = " << rk.getValue()
      << "; backLink = " << rk.getBackLink();
   return os;
}

bool GeoNode::operator < (GeoNode& right)
{
   return value < right.getValue();
}

bool GeoNode::operator <= (GeoNode& right)
{
   return value <= right.getValue();
}

bool GeoNode::operator > (GeoNode& right)
{
   return value > right.getValue();
}

bool GeoNode::operator >= (GeoNode& right)
{
   return value >= right.getValue();
}

#endif /* GEONODE_H_ */
