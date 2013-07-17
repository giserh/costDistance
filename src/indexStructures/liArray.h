/*
 * liArray.h
 *
 *  Created on: Jul 16, 2013
 *      Author: cjgrady
 */

#ifndef LIARRAY_H_
#define LIARRAY_H_


#include <vector>
#include <exception>

#include "indexStructure.h"

template <class NodePtr>
class LIArray : public IndexStructure<NodePtr>
{
private:
   //std::vector<NodePtr *> items;
   NodePtr ** items;
   int iSize;
public:
   LIArray();
   LIArray(int size);
   virtual ~LIArray();

   void setSize(int size);

   virtual NodePtr * get(int idx);
   virtual void insert(int idx, NodePtr * ptr);
   virtual void rm(int idx);
   virtual void reset();
};

template <class NodePtr>
LIArray<NodePtr>::LIArray()
{
   iSize = 100;
   reset();
}

template <class NodePtr>
LIArray<NodePtr>::LIArray(int size)
{
   iSize = size;
   reset();
}

template <class NodePtr>
LIArray<NodePtr>::~LIArray()
{
   //items.clear();
   delete [] items;
}

template <class NodePtr>
void LIArray<NodePtr>::setSize(int size)
{
   iSize = size;
}

template <class NodePtr>
NodePtr * LIArray<NodePtr>::get(int idx)
{
   if (items[idx] == NULL)
      throw DNEException();

   if (items[idx])
      return items[idx];
   else
      throw DNEException();
//   if (items[idx] == 0)
//      throw DNEException();
//   else
//      return items[idx];
}

template <class NodePtr>
void LIArray<NodePtr>::insert(int idx, NodePtr * ptr)
{
   try
   {
      items[idx] = ptr;
   }
   catch (std::exception &e)
   {
      std::cout << "Throwing exception on insert: " << idx << endl;
      throw;
   }
}

template <class NodePtr>
void LIArray<NodePtr>::rm(int idx)
{
   if (items[idx] == 0)
      std::cout << "Trying to delete null index: " << idx << endl;
   delete items[idx];
   items[idx] = 0;
}

template <class NodePtr>
void LIArray<NodePtr>::reset()
{
   std::cout << "Trying to resize array: " << iSize << endl;
   items = new NodePtr *[iSize];
   for (int i=0; i < iSize; i++)
      items[i] = 0;
//   items.resize(iSize, NULL);
//   for (int i=0; i < items.size(); i++)
//      items[i] = new NodePtr;
}

#endif /* LIARRAY_H_ */
