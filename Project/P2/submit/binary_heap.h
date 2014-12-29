#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "eecs281priority_queue.h"


//A specialized version of the 'heap' ADT implemented as a binary heap.
template<typename TYPE, typename COMP = std::less<TYPE>>
class binary_heap : public eecs281priority_queue<TYPE, COMP> {
public:
  typedef unsigned size_type;

  //Description: Construct a heap out of an iterator range with an optional
  //             comparison functor.
  //Runtime: O(n) where n is number of elements in range.
  template<typename InputIterator>
  binary_heap(InputIterator start, InputIterator end, COMP comp = COMP());

  //Description: Construct an empty heap with an optional comparison functor.
  //Runtime: O(1)
  binary_heap(COMP comp = COMP());

  //Description: Assumes that all elements inside the heap are out of order and
  //             'rebuilds' the heap by fixing the heap invariant.
  //Runtime: O(n)
  virtual void make_heap();

  //Description: Add a new element to the heap.
  //Runtime: O(log(n))
  virtual void push(const TYPE& val);

  //Description: Remove the most extreme (defined by 'compare') element from
  //             the heap.
  //Note: We will not run tests on your code that would require it to pop an
  //element when the heap is empty. Though you are welcome to if you are
  //familiar with them, you do not need to use exceptions in this project.
  //Runtime: O(log(n))
  virtual void pop();

  //Description: Return the most extreme (defined by 'compare') element of
  //             the heap.
  //Runtime: O(1)
  virtual const TYPE& top() const;

  //Description: Get the number of elements in the heap.
  //Runtime: O(1)
  virtual size_type size() const
    { /*** Fill this in - might be very simple depending on implementation ***/
	return data.size();
    }

  //Description: Return true if the heap is empty.
  //Runtime: O(1)
  virtual bool empty() const
    { /*** Fill this in - might be very simple depending on implementation ***/ 
	return data.empty();
    }
private:
  //Note: This vector *must* be used your heap implementation.
  std::vector<TYPE> data;
private:
  //***Add any additional member functions or data you require here.
  void fixUp(std::vector<TYPE>& data, int k){
	while(k != 1){
		if(!this->compare(data[k-1], data[k/2 - 1])) break;
		swap(data[k-1], data[k/2 -1]);
		k = k / 2;
	}
  }
  void fixDown(std::vector<TYPE>& data, int k, int heapSize){
	int j = 2 * k;
	while(j <= heapSize){
		if(j < heapSize && !this->compare(data[j-1], data[j])) j++;
		if(this->compare(data[k-1], data[j-1])) break;
		swap(data[k-1], data[j-1]);
		k = j;
		j = 2 * k;
	}
  }
  void swap(TYPE& a, TYPE& b){
	TYPE temp = a;
	a = b;
	b = temp;
  }
};
template<typename TYPE, typename COMP>
template<typename InputIterator>
binary_heap<TYPE, COMP>::binary_heap(
  InputIterator start,
  InputIterator end,
  COMP comp
) {
	this->compare = comp;
	while(start != end){
		data.push_back(*start);
		start++;
	}
	make_heap();
}

template<typename TYPE, typename COMP>
binary_heap<TYPE, COMP>::binary_heap(COMP comp) {
	this->compare = comp;
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::make_heap() {
	//unsigned int i = data.size();
	//i = i / 2;
	//unsigned int k = i / 2;
	//while(k > 0){
	for(int k = data.size()/2; k > 0; k--){
		fixDown(data, k, data.size());
		//k = k--;
	}
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::push(const TYPE& val) {
	data.push_back(val);
	fixUp(data, data.size());
}

template<typename TYPE, typename COMP>
void binary_heap<TYPE, COMP>::pop() {
	swap(data[0], data.back());
	data.pop_back();
	fixDown(data, 1, data.size());
}

template<typename TYPE, typename COMP>
const TYPE& binary_heap<TYPE, COMP>::top() const {
  return data[0]; //This line present only so that this provided file compiles.
}

/*template<typename TYPE>
void swap(TYPE& a, TYPE& b){
	TYPE temp = a;
	a = b;
	b = temp;
}

template<typename TYPE>
void fixUp(std::vector<TYPE>& data, int k){
	while(k != 1){
		if(!this->compare(data[k-1], data[k/2 - 1])) break;
		swap(data[k-1], data[k/2 -1]);
		k = k / 2;
	}
}

template<typename TYPE>
void fixDown(std::vector<TYPE>& data, int k, int heapSize){
	int j = 2 * k;
	while(j <= heapSize){
		if(j < heapSize && !this->compare(data[j-1], data[j])) j++;
		if(this->compare(data[k], data[j])) break;
		swap(data[k-1], data[j]);
		k = j;
		j = 2 * k;
	}
}*/
#endif //BINARY_HEAP_H

