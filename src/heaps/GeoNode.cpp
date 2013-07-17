/*
 * GeoNode.cpp
 *
 *  Created on: May 29, 2013
 *      Author: cjgrady
 */

#include "GeoNode.h"

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



