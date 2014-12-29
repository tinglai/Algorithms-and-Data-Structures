#ifndef PAIRING_HEAP_H
#define PAIRING_HEAP_H

#include "eecs281priority_queue.h"


//A specialized version of the 'heap' ADT implemented as a pairing heap.
template<typename TYPE, typename COMP = std::less<TYPE>>
class pairing_heap : public eecs281priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  //Description: Construct a heap out of an iterator range with an optional
  //             comparison functor.
  //Runtime: O(n) where n is number of elements in range.
  template<typename InputIterator>
  pairing_heap(InputIterator start, InputIterator end, COMP comp = COMP());

  //Description: Construct an empty heap with an optional comparison functor.
  //Runtime: O(1)
  pairing_heap(COMP comp = COMP());
  
  //Description: Copy constructor.
  //Runtime: O(n)
  pairing_heap(const pairing_heap& other);
  
  //Description: Copy assignment operator.
  //Runtime: O(n)
  pairing_heap& operator=(const pairing_heap& rhs);
  
  //Description: Destructor
  //Runtime: O(n)
  ~pairing_heap();

  //Description: Assumes that all elements inside the heap are out of order and
  //             'rebuilds' the heap by fixing the heap invariant.
  //Runtime: O(n)
  virtual void make_heap();

  //Description: Add a new element to the heap. This has been provided for you,
  //             in that you should implement push functionality in the
  //             add_node function.
  //Runtime: Amortized O(1)
  virtual void push(const TYPE& val) { add_node(val); }

  //Description: Remove the most extreme (defined by 'compare') element from
  //             the heap.
  //Note: We will not run tests on your code that would require it to pop an
  //element when the heap is empty. Though you are welcome to if you are
  //familiar with them, you do not need to use exceptions in this project.
  //Runtime: Amortized O(log(n))
  virtual void pop();

  //Description: Return the most extreme (defined by 'compare') element of
  //             the heap.
  //Runtime: O(1)
  virtual const TYPE& top() const;

  //Description: Get the number of elements in the heap.
  //Runtime: O(1)
  virtual size_type size() const { /*** Fill this in ***/ }

  //Description: Return true if the heap is empty.
  //Runtime: O(1)
  virtual bool empty() const { /*** Fill this in ***/ }

  class Node {
    //This node class will allow external users to update the priority of
    //elements that are already inside the heap.
  public:
    //***Add any constructors you need here.
  public:
    //Description: Allows access to the element at that Node's position.
    //Runtime: O(1) - this has been provided for you.
    const TYPE& operator*() const { return elt; }

    //The following line allows you to access any private data members of this
    //Node class from within the pairing_heap class. (ie: myNode.elt is a legal
    //statement in pairing_heap's add_node() function).
    friend pairing_heap;
  private:
    TYPE elt;
  private:
    //***Add any additional member functions or data you require here.
  };

  //Description: Updates the priority of an element already in the heap by
  //             replacing the element refered to by the Node with new_value.
  //             Must maintain heap invariants.
  //
  //PRECONDITION: The new priority, given by 'new_value' must be more extreme
  //              (as defined by comp) than the old priority.
  //
  //Runtime: As discussed in reading material.
  void updateElt(Node* node, TYPE new_value);

  //Description: Add a new element to the heap. Returns a Node* corresponding
  //             to the newly added element.
  //Runtime: Amortized O(1)
  Node* add_node(const TYPE& val);

private:
  //***Add any additional member functions or data you require here.
  //***We recommend creating a 'meld' function (see the reading).
};

template<typename TYPE, typename COMP>
template<typename InputIterator>
pairing_heap<TYPE, COMP>::pairing_heap(
  InputIterator start,
  InputIterator end,
  COMP comp
) {
  //Your code.
}

template<typename TYPE, typename COMP>
pairing_heap<TYPE, COMP>::pairing_heap(COMP comp) {
  //Your code.
}

template<typename TYPE, typename COMP>
pairing_heap<TYPE, COMP>::pairing_heap(const pairing_heap& other) {
  //Your code.
}

template<typename TYPE, typename COMP>
pairing_heap<TYPE, COMP>&
pairing_heap<TYPE, COMP>::operator=(const pairing_heap& rhs) {
  //Your code.
}

template<typename TYPE, typename COMP>
pairing_heap<TYPE, COMP>::~pairing_heap() {
  //Your code.
}

template<typename TYPE, typename COMP>
void pairing_heap<TYPE, COMP>::make_heap() {
  //Your code.
}

template<typename TYPE, typename COMP>
void pairing_heap<TYPE, COMP>::pop() {
  //Your code.
}

template<typename TYPE, typename COMP>
const TYPE& pairing_heap<TYPE, COMP>::top() const {
  //Your code.
  return TYPE(); //This line present only so that this provided file compiles.
}

template<typename TYPE, typename COMP>
typename pairing_heap<TYPE, COMP>::Node*
pairing_heap<TYPE, COMP>::add_node(const TYPE& val) {
  //Your code.
}

template<typename TYPE, typename COMP>
void pairing_heap<TYPE, COMP>::updateElt(Node* node, TYPE new_value) {
  //Your code.
}

#endif //PAIRING_HEAP_H

