/*
 * FibHeap.h
 *
 *  Created on: Oct 10, 2012
 *      Author: cjgrady
 *
 * FibHeap is an implementation of a Fibonacci heap.
 */

// write reset min to take a minimum pointer so that it can use the
// same code for any node

// re-write merge to work at any level



#ifndef FIBHEAP_H_
#define FIBHEAP_H_

#include <iostream>
using namespace std;

template <class HeapKey>
struct Node
{
   Node * min;
   Node * parent;
   Node * leftSib;
   Node * rightSib;
   int degree;
   HeapKey key;
};

template <class HeapKey>
class FibHeap
{
   Node<HeapKey> * min;
public:
   FibHeap()
   {
      min = 0;
   }

   ~FibHeap()
   {
      while (min != 0)
      {
         pop();
      }
   }

   bool empty()
   {
      if (min == 0)
         return true;
      else
         return false;
   }

   HeapKey pop()
   {
      HeapKey ret;
      Node<HeapKey> * tmp;
      tmp = min;
      ret = min->key;
      if (min->leftSib == min)
      {
         min = min->min;
      }
      else if (min->min)
      {
         min->min->parent = 0;
         min->leftSib->rightSib = min->min;
         min->rightSib->leftSib = min->min->leftSib;
         min->min->leftSib->rightSib = min->rightSib;
         min->min->leftSib = min->leftSib;
         min = min->rightSib;
         resetMin(min);
         merge();
      }
      else
      {
         min->leftSib->rightSib = min->rightSib;
         min->rightSib->leftSib = min->leftSib;
         min = min->rightSib;
         resetMin(min);
         //merge
         resetMin();
         merge();
      }
      return ret;
   }

   Node<HeapKey> * push(HeapKey key)
   {
      Node<HeapKey> * ret;
      if (!min)
      {
         min = new Node<HeapKey>;
         min->key = key;
         min->degree = 1;
         min->leftSib = min;
         min->rightSib = min;
         min->min = 0;
         min->parent = 0;
         ret = min;
      }
      else
      {
         Node<HeapKey> * tmp;
         tmp = new Node<HeapKey>;
         tmp->key = key;
         tmp->leftSib = min;
         tmp->rightSib = min->rightSib;
         tmp->min = 0;
         tmp->parent = 0;
         tmp->degree = 1;
         tmp->rightSib->leftSib = tmp;
         tmp->leftSib->rightSib = tmp;
         ret = tmp;
      }
      resetMin(min);
      return ret;
   }

   void decreaseKey(Node<HeapKey> * ptr)
   {
      Node<HeapKey> * parentPtr = 0;

      if (inMyRow(ptr, min))
      {
         //cout << "In minimum row, pass" << endl;
      }
      else
      {
         // check for siblings
         if (ptr->rightSib != ptr)
         {
            // has siblings
            ptr->leftSib->rightSib = ptr->rightSib;
            ptr->rightSib->leftSib = ptr->leftSib;

            if (ptr->parent != 0)
            {
               // need to reset min
               ptr->parent->min = findMin(ptr->leftSib);
               ptr->parent->min->parent = ptr->parent;
               parentPtr = ptr->parent;
               //fixDegree(ptr->parent);

               ptr->parent = 0;
            }
            else
            {
               if (findMin(ptr->leftSib)->parent != 0)
               {
                  parentPtr = findMin(ptr->leftSib)->parent;
                  //fixDegree(findMin(ptr->leftSib)->parent);
               }
               ptr->parent = 0;
            }
         }
         else
         {
            // no siblings
            ptr->parent->min = 0;
            fixDegree(ptr->parent);
            ptr->parent = 0;
         }
         ptr->leftSib = min->leftSib;
         ptr->rightSib = min;
         min->leftSib->rightSib = ptr;
         min->leftSib = ptr;

         if (parentPtr != 0)
            fixDegree(parentPtr);
      }
      min = findMin(min);
   }

   bool integrityCheck(Node<HeapKey> * ptr)
   {
      Node<HeapKey> * t;
      bool valid = true;
      t = ptr;

      // Need to make sure there is a parent in the row

      //cout << "Integrity check on " << ptr << endl;
      if (min != 0)
      {
         if (ptr != min)
         {
            if (ptr->parent == 0)
            {
               cout << "Parent of " << ptr << " was zero" << endl;
               valid = false;
               throw 1;
               return false;
            }
         }

         do
         {
            //cout << "Integrity check on " << t << endl;
            // check left
            if (t->leftSib->rightSib != t)
            {
               valid = false;
               cout << "Left sibling mismatch for " << t << endl;
               throw 2;
               return false;
            }
            // check right
            if (t->rightSib->leftSib != t)
            {
               valid = false;
               cout << "Right sibling mismatch for " << t << endl;
               throw 3;
               return false;
            }

            if (t->min != 0)
            {
               if (t->degree <= 1)
               {
                  valid = false;
                  cout << "Degree of " << t << " is " << t->degree << " but it has children " << endl;
                  throw 4;
                  return false;
               }

               if (t->min->parent != t)
               {
                  valid = false;
                  cout << "Parent of child: " << t->min << " is " << t->min->parent << " instead of " << t << endl;
                  throw 5;
                  return false;
               }

               if (not integrityCheck(t->min))
                  return false;
               //valid = valid && integrityCheck(t->min);
            }

            if (t != ptr)
            {
               if (t->parent != 0)
               {
                  cout << "Sibling of " << ptr << ", " << t << " has parent " << t->parent << endl;
                  throw 6;
                  return false;
               }
            }

            t = t->rightSib;
         } while (t != ptr);
      }
      else
         cout << "Min == 0" << endl;
      return valid;
   }

private:

   void evalPointer(Node<HeapKey> * ptr, int ref)
   {
      if (ptr == 0)
         cout << "Pointer is 0! ptr: " << ptr << " ref: " << ref << endl;
      else
      {
         cout << " min: " << ptr->min << endl;
         cout << " parent: " << ptr->parent << endl;
         cout << " left: " << ptr->leftSib << endl;
         cout << " right: " << ptr->rightSib << endl;
         cout << " value: " << ptr->key.getValue() << endl;
         cout << " index: " << ptr->key.getIndex() << endl;
         cout << " backlink: " << ptr->key.getBackLink() << endl;
      }
      if (ptr->leftSib == 0)
      {
         cout << "Left sibling is 0. ptr: " << ptr << " ref: " << ref << endl;
         cout << " value: " << ptr->key.getValue() << endl;
         cout << " index: " << ptr->key.getIndex() << endl;
      }
      if (ptr->rightSib == 0)
      {
         cout << "Right sibling is 0. ptr: " << ptr << " ref: " << ref << endl;
         cout << " value: " << ptr->key.getValue() << endl;
         cout << " index: " << ptr->key.getIndex() << endl;
      }
   }

   Node<HeapKey> * findMin(Node<HeapKey> * ptr)
   {
      //cout << "Start find min" << endl;
      Node<HeapKey> * minPtr;
      Node<HeapKey> * t;

      t = ptr->leftSib;
      if (t->rightSib != ptr)
      {
//         cout << "Inconsistency between " << ptr << " and " << t << endl;
//         cout << "Ptr value: " << ptr->key.getValue() << endl;
//         cout << "Ptr key: " << ptr->key.getIndex() << endl;
      }
      minPtr = ptr;
      while (t != ptr)
      {
         if (t->key < minPtr->key)
         {
            minPtr = t;
         }
         if (t->leftSib->rightSib != t)
         {
//            cout << "Inconsistency between " << long(t) << " and " << t->leftSib << endl;
//            cout << "T - value: " << t->key.getValue() << endl;
         }
         t = t->leftSib;
      }
      return minPtr;
   }

   bool inMyRow(Node<HeapKey> * ptr, Node<HeapKey> * ptr2)
   {
      Node<HeapKey> * t;
      t = ptr->rightSib;
      while (t != ptr)
      {
         if (ptr2 == t)
         {
            cout << "end in my row(true) " << endl;
            return true;
         }
         t = t->rightSib;
      }
      return false;
   }

   int findMaxDegree(Node<HeapKey> * ptr)
   {
      Node<HeapKey> * t;
      int maxDegree = 0;
      maxDegree = ptr->degree;
      t = ptr->rightSib;
      while (t != ptr)
      {
         if (t->degree > maxDegree)
            maxDegree = t->degree;
         t = t->rightSib;
      }
      return maxDegree;
   }

   void fixDegree(Node<HeapKey> * ptr)
   {
      Node<HeapKey> * parent;
      Node<HeapKey> * minPtr;
      Node<HeapKey> * t;
      int maxDegree = 0;
      if (ptr == 0)
         return;

      if (ptr->min != 0)
      {
         maxDegree = ptr->min->degree;
         t = ptr->min->rightSib;
         while(t != ptr->min)
         {
            if (t->degree > maxDegree)
            {
               maxDegree = t->degree;
            }
            t = t->rightSib;
         }
      }

      // check degree
      if (ptr->degree != (maxDegree+1))
      {
         ptr->degree = maxDegree + 1;
         // get parent
         minPtr = findMin(ptr);
         if (minPtr->parent != 0)
         {
            fixDegree(minPtr->parent);
         }
      }
   }

   void resetMin(Node<HeapKey> * &minPtr)
   {
      Node<HeapKey> * p2;
      p2 = minPtr->rightSib;
      while (minPtr != p2)
      {
         if (p2->key < minPtr->key)
         {
            minPtr = p2;
         }
         p2 = p2->rightSib;
      }
   }

   void resetMin()
   {
      Node<HeapKey> * p2;
      p2 = min->rightSib;
      while (min != p2)
      {
         if (p2->key < min->key)
         {
            min = p2;
         }
         p2 = p2->rightSib;
      }
   }

   void merge()
   {
      Node<HeapKey> * ptr;
      ptr = min;
      Node<HeapKey> * p2;
      int maxDegree;
      int i = 1;
      Node<HeapKey> * f;
      Node<HeapKey> * parent;
      Node<HeapKey> * child;
      f = 0;
      parent = 0;
      child = 0;
      // Find maximum degree
      // ptr will always be root
      // loop looking for matching degrees until back at min
      //  if merging two branches, check the new degree and increase max degree if needed
      // loop until max degree
      maxDegree = ptr->degree;
      p2 = ptr->rightSib;
      while (ptr != p2)
      {
         if (p2->degree > maxDegree)
           maxDegree = p2->degree;
         p2 = p2->rightSib;
      }

      while (i <= maxDegree)
      {
         if (ptr->degree == i)
            f = ptr;
         p2 = ptr->rightSib;
         //evalPointer(p2, 20);
         while (ptr != p2)
         {
            if (p2->degree == i)
            {
               if (!f)
                  f = p2;
               else
               {
                  if (f->key <= p2->key)
                  {
                     parent = f;
                     child = p2;
                  }
                  else
                  {
                     parent = p2;
                     child = f;
                  }
                  if (f == p2)
                  {
                     cout << "Sanity check failed!" << endl;
                  }
                  else
                  {
                     parent->degree++;
                     if (parent->degree > maxDegree)
                        maxDegree = parent->degree;
                     child->leftSib->rightSib = child->rightSib;
                     //evalPointer(child, 21);
                     //evalPointer(child->rightSib, 22);
                     child->rightSib->leftSib = child->leftSib;
                     //evalPointer(child, 23);
                     //evalPointer(child->leftSib, 24);
                     if (parent->min)
                     {
                        child->leftSib = parent->min;
                        child->rightSib = parent->min->rightSib;
                        child->rightSib->leftSib = child;
                        child->leftSib->rightSib = child;
                        //evalPointer(child->leftSib, 25);
                        //evalPointer(child->rightSib, 26);
                        if (child->key < parent->min->key)
                        {
                           parent->min->parent = 0;
                           parent->min = child;
                           child->parent = parent;
                        }
                     }
                     else
                     {
                        parent->min = child;
                        child->parent = parent;
                        child->rightSib = child;
                        child->leftSib = child;
                     }
                     f = 0;
                     p2 = ptr;
                     child = 0;
                     parent = 0;
                  }
               }
            }
            p2 = p2->rightSib;
         }
         i++;
      }
   }
};



#endif /* FIBHEAP_H_ */
