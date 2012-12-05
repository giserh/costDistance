/*
 * GeoHeap.h
 *
 *  Created on: Oct 10, 2012
 *      Author: cjgrady
 *
 * A GeoHeap will wrap an underlying heap and include a hash table so that
 *    existing entries can be checked instead of entering duplicate values
 */

#ifndef GEOHEAP_H_
#define GEOHEAP_H_

#include "FibHeap.h"
#include "geoHash.h"
//#include "GeoNode.h"

#include <iostream>

using namespace std;

template <class HeapKey>
class GeoHeap
{
   FibHeap<HeapKey> heap;
   HashTable< Node<HeapKey> > ht;

	// Hash table pointing at nodes

public:
	GeoHeap()
	{

	}

	~GeoHeap()
	{

	}

	bool empty()
	{
	   return heap.empty();
	}

	HeapKey pop()
	{
	   HeapKey ret;
	   ret = heap.pop();
	   ht.rm(ret.getIndex());
	   return ret;
	}

	void push(HeapKey n)
	{
      HashNode< Node<HeapKey> > * ptr;
      Node<HeapKey> * ptr2;
	   ptr = ht.get(n.getIndex());
	   if (ptr == 0)
	   {
   	   ptr2 = heap.push(n);
   	   ht.insert(n.getIndex(), ptr2);
	   }
	   else
	   {
	      // check if the new key is less
	      if (n.getValue() < ptr->ptr->key.getValue())
	      {
	         ptr->ptr->key.setValue(n.getValue());
	         heap.decreaseKey(ptr->ptr);
	      }
	   }
	}
};

#endif /* GEOHEAP_H_ */
