/*
 * indexStructure.h
 *
 *  Created on: Jul 15, 2013
 *      Author: cjgrady
 */

#ifndef INDEXSTRUCTURE_H_
#define INDEXSTRUCTURE_H_

class DNEException : public std::exception
{
   virtual const char* what() const throw()
   {
      return "Element does not exist";
   }
};

template <class NodePtr>
class IndexStructure
{
   public:
      virtual NodePtr * get(int idx);
      virtual void insert(int idx, NodePtr * ptr);
      virtual void rm(int idx);
      virtual void reset();
      virtual ~IndexStructure();
};

template <class NodePtr>
NodePtr * IndexStructure<NodePtr>::get(int idx)
{
   return 0;
}

template <class NodePtr>
void IndexStructure<NodePtr>::insert(int idx, NodePtr * ptr)
{

}

template <class NodePtr>
void IndexStructure<NodePtr>::rm(int idx)
{

}

template <class NodePtr>
void IndexStructure<NodePtr>::reset()
{

}

template <class NodePtr>
IndexStructure<NodePtr>::~IndexStructure()
{

}

#endif /* INDEXSTRUCTURE_H_ */
