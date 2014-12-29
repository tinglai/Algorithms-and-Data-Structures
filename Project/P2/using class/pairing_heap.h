#ifndef PAIRING_HEAP_H
#define PAIRING_HEAP_H

#include "eecs281priority_queue.h"
#include <vector>
#include <iostream>


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
  virtual size_type size() const { return heapSize;/*** Fill this in ***/ }

  //Description: Return true if the heap is empty.
  //Runtime: O(1)
  virtual bool empty() const { return (heapSize == 0);/*** Fill this in ***/ }


  class Node {
    //This node class will allow external users to update the priority of
    //elements that are already inside the heap.
  public:
    //***Add any constructors you need here.
    Node(TYPE in):elt(in){
	next = nullptr;
	pre = nullptr;
	child = nullptr;
	}
    Node(){
	next = nullptr;
	pre = nullptr;
	child = nullptr;
	}
    //Node(Node& other):elt(other.elt), next(other.next),
    //                  pre(other.pre), child(other.child){}
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
	Node* next;
	Node* pre;
	Node* child;
	void detach(){
		//root
		if(!pre){
			child->pre = nullptr;
			child = nullptr;
		}
		//leftmost
		else if(pre->child == this){
			pre->child = next;
			if(next) next->pre = pre;
			pre = nullptr;
			next = nullptr;
			}
		else{
			pre->next = next;
			if(next) next->pre = pre;
			pre = nullptr;
			next = nullptr;
		}
	}
    //***Add any additional member functions or data you require here.
  };//Node

void info(Node* r){
	if(!r) return;
	info(r->child);
	info(r->next);
	std::cout<<"****"<<(r->elt)<<' '<<(r->elt)<<"****"<<std::endl;
}
void print(){
info(root);
}


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
  //             to the newly added element.There is no way to rem
  //Runtime: Amortized O(1)
  Node* add_node(const TYPE& val);

private:
	unsigned int heapSize;
	Node* root;
	Node* meld(Node* a, Node* b){
		if(!a) return b;
		if(!b) return a;
		if(this->compare(a->elt, b->elt)){
			if(a->child){
				Node* c = a->child;
				b->next = c;
				c->pre = b;
			}
			a->child = b;
			b->pre = a;
			return a;
		}
		else{
			if(b->child){
				Node* c = b->child;
				a->next = c;
				c->pre = a;
			}
			b->child = a;
			a->pre = b;
			return b;
		}
	}

	Node* copy(Node* in, Node* pofin){
		Node* a = new Node;
		a->elt = in->elt;
		a->pre = pofin;
		if(in->child){
			a->child = copy(in->child, a);
		}
		if(in->next){
			a->next = copy(in->next, a);
		}
		return a;
	}
	/*void del(Node* n){
		if(!n) return;
		if(n->child)del(n->child);
		if(n->next)del(n->next);
		delete n;
		n = nullptr;
	}
*/
	void del(Node* n){
		if(!n) return;
		std::vector<Node*> dd;
		Node* temp;
		if(n->child){
			dd.push_back(n->child);
		}
		delete(n);
		while(!dd.empty()){
			temp = dd.back();
			dd.pop_back();
			if(temp->child){
				dd.push_back(temp->child);
			}
			if(temp->next){
				dd.push_back(temp->next);
			}
			delete temp;
		}
	}
	Node* fix(Node* in, Node* r){
		if(in->child){
			r = fix(in->child, r);
			r->pre = nullptr;
			r->next = nullptr;
			in->pre = nullptr;
			in->child = nullptr;
		}
		if(in->next){
			r = fix(in->next, r);
			r->pre = nullptr;
			r->next = nullptr;
			in->pre = nullptr;
			in->next = nullptr;
		}
		r = meld(in, r);
		return r;
	}

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
	if(start == end){
		heapSize = 0;
		this->compare = comp;
		root = nullptr;
		return;
	}
	Node* r = new Node(*start);
	start++;
	heapSize = 1;
	while(start != end){
		Node* in = new Node(*start);
		r = meld(r, in);
		start++;
		heapSize++;
	}
	root = r;
	this->compare = comp;
}

template<typename TYPE, typename COMP>
pairing_heap<TYPE, COMP>::pairing_heap(COMP comp) {
  //Your code.
	heapSize = 0;
	root = nullptr;
	this->compare = comp;
}

template<typename TYPE, typename COMP>
pairing_heap<TYPE, COMP>::pairing_heap(const pairing_heap& other) {
  //Your code.
	heapSize = other.heapSize;
	Node* emp = nullptr;
	Node* in = other.root;
	root = copy(in, emp);
	this->compare = other.compare;
}

template<typename TYPE, typename COMP>
pairing_heap<TYPE, COMP>&
pairing_heap<TYPE, COMP>::operator=(const pairing_heap& rhs) {
  //Your code.
	if(this == &rhs) return *this;
	del(root);
	heapSize = rhs.heapSize;
	Node* emp = nullptr;
	Node* in = rhs.root;
	Node* t = copy(in, emp);
	root = t;
	return *this;
	this->compare = rhs.compare;
}

template<typename TYPE, typename COMP>
pairing_heap<TYPE, COMP>::~pairing_heap() {
  //Your code.
	del(root);
}

template<typename TYPE, typename COMP>
void pairing_heap<TYPE, COMP>::make_heap() {
  //Your code.
	Node* l = nullptr;
	root = fix(root, l);
}

template<typename TYPE, typename COMP>
void pairing_heap<TYPE, COMP>::pop() {
  //Your code.
 	if(!root->child){
		delete root;
		heapSize--;
		root = nullptr;
		return;
	}
	Node* a; 
	Node* b;
	Node* temp;

	std::vector<Node*> qq;
	a = root->child;
	a->pre = nullptr;
	b = a->next;
	delete root;////////////////////////
	if(!b){
		temp = b;
	}
	else{
		temp = b->next;
		b->next = nullptr;
		b->pre = nullptr;
	}
	a->next = nullptr;
	a->pre = nullptr;
	a = meld(a, b);
	qq.push_back(a);
	a = temp;
	
	while(a){
		b = a->next;
		if(!b) temp = b;
		else{
			temp = b->next;
			b->next = nullptr;
			b->pre = nullptr;
		}
		a->next = nullptr;
		a->pre = nullptr;
		a = meld(a, b);
		qq.push_back(a);
		a = temp;
	}
	while(qq.size() > 1){
		a = qq.back();
		qq.pop_back();
		b = qq.back();
		qq.pop_back();
		a = meld(a, b);
		qq.push_back(a);
	}
	root = qq.back();
	heapSize--;
	/*
	Node* a;
	a = root->child;
	a->pre = nullptr;
	delete root;
	root = a;
	make_heap();
	heapSize--;
	*/
}

template<typename TYPE, typename COMP>
const TYPE& pairing_heap<TYPE, COMP>::top() const {
  //Your code.
  return root->elt; //This line present only so that this provided file compiles.
}

template<typename TYPE, typename COMP>
typename pairing_heap<TYPE, COMP>::Node*
pairing_heap<TYPE, COMP>::add_node(const TYPE& val) {
  //Your code.
	Node* a = new Node(val);
	root = meld(a, root);
	heapSize++;
	return a;
}

template<typename TYPE, typename COMP>
void pairing_heap<TYPE, COMP>::updateElt(Node* node, TYPE new_value) {
  //Your code.
	if(!node) return;
	if(!this->compare(new_value, node->elt)) return;
	if(node == root){
		node->elt = new_value;
		return;
	}
	else{
		node->elt = new_value;
		node->detach();
		node->pre = nullptr;
		node->next = nullptr;
		root = meld(node, root);
	}
}

#endif //PAIRING_HEAP_H
