/*
 * geoHash.h
 *
 *  Created on: Oct 22, 2012
 *      Author: cjgrady
 */

#ifndef GEOHASH_H_
#define GEOHASH_H_

#include <vector>

template <class NodePtr>
struct HashNode
{
   int index;
   NodePtr * ptr;
   HashNode<NodePtr> * next;
};

template <class NodePtr>
class HashTable
{
private:
   int numBuckets;
   //HashNode<NodePtr> **ht;
   vector<HashNode<NodePtr>*> ht;
public:
   HashTable<NodePtr>();
   HashTable<NodePtr>(int numBuckets);

   HashNode<NodePtr> * get(int idx);
   void insert(int idx, NodePtr * ptr);
   void rm(int idx);
   void reset();
};

template <class NodePtr>
HashTable<NodePtr>::HashTable()
{
   numBuckets = 100;
   ht.resize(numBuckets, 0);
}

template <class NodePtr>
HashTable<NodePtr>::HashTable(int numB)
{
   numBuckets = numB;
   ht.resize(numBuckets, 0);
}

template <class NodePtr>
HashNode<NodePtr> * HashTable<NodePtr>::get(int idx)
{
   HashNode<NodePtr> * ptr;
   int bucket;
   bucket = idx % numBuckets;
   ptr = ht[bucket];
   while (ptr != 0 && ptr->index != idx)
   {
      ptr = ptr->next;
   }
   return ptr;
}

template <class NodePtr>
void HashTable<NodePtr>::insert(int idx, NodePtr * ptr)
{
   //cout << "a" << endl;
   HashNode<NodePtr> * nextPtr;
   //cout << "b" << endl;
   int bucket;
   //cout << "c" << endl;
   bucket = idx % numBuckets;
   //cout << "d" << endl;
   nextPtr = ht[bucket];
   //cout << "e" << endl;
   //cout << "Bucket: " << bucket << endl;
   //cout << "ht[bucket]" << ht[bucket] << endl;

   HashNode<NodePtr> newNode;
   newNode.index = idx;
   newNode.next = nextPtr;
   newNode.ptr = ptr;
   ht[bucket] = & newNode;

   //ht[bucket] = new HashNode<NodePtr>();
   //cout << "f" << endl;
   //ht[bucket]->index = idx;
   //cout << "g" << endl;
   //ht[bucket]->next = nextPtr;
   //cout << "h" << endl;
   //ht[bucket]->ptr = ptr;
   //cout << "i" << endl;
}

template <class NodePtr>
void HashTable<NodePtr>::rm(int idx)
{
   HashNode<NodePtr> * prev;
   HashNode<NodePtr> * n;
   int bucket;
   bucket = idx % numBuckets;

   if (ht[bucket]->index == idx)
   {
      prev = ht[bucket];
      ht[bucket] = ht[bucket]->next;
      delete prev;
   }
   else
   {
      prev = ht[bucket];
      n = prev->next;

      while (n != 0 && n->index != idx)
      {
         prev = n;
         n = n->next;
      }

      if (n != 0)
      {
         prev->next = n->next;
         delete n;
      }
   }
}

template <class NodePtr>
void HashTable<NodePtr>::reset()
{
   for (int i = 0; i < numBuckets; i++)
   {
      ht[i] = 0;
   }
}

#endif /* GEOHASH_H_ */
