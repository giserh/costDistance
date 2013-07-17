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

#endif /* GEONODE_H_ */
