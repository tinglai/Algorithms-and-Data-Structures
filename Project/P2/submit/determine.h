#ifndef GUARD_determine_h
#define GUARD_determine_h
#include "eecs281priority_queue.h"
#include "poorman_priority_queue.h"
#include "sorted_priority_queue.h"
#include "binary_heap.h"
#include "zombie.h"
#include <list>

template<typename TYPE>
class compList{
private:
	bool less;
public:
	compList(bool isLess):less(isLess){}
	compList():less(1){}
	bool operator()(const TYPE& a, const TYPE& b) const {
		if(less){
			if ((*a)->getETA() < (*b)->getETA())
				return 1;
			else {
				if ((*a)->getETA() == (*b)->getETA())
					return (*a)->name < (*b)->name;
				else 
					return 0;
			}//else
		}//if
		else{
			if ((*a)->getETA() > (*b)->getETA())
				return 1;
			else {
				if ((*a)->getETA() == (*b)->getETA())
					return (*a)->name > (*b)->name;
				else 
					return 0;
			}//else
		}
	}//bool operator()
};

//eecs281priority_queue<std::list<Zombie*>::iterator, 
  //  compList<std::list<Zombie*>::iterator>> determine(int);

/*eecs281priority_queue<std::list<Zombie*>::iterator, 
    compList<std::list<Zombie*>::iterator>>* determine(int container){
	if(container == 1){
		binary_heap<std::list<Zombie*>::iterator, 
                               compList<std::list<Zombie*>::iterator>>* 
		                                               b_heap = 
			new binary_heap<std::list<Zombie*>::iterator, 
                               compList<std::list<Zombie*>::iterator>>;
		return b_heap;
	}

	if(container == 2){
		poorman_priority_queue<std::list<Zombie*>::iterator, 
                               compList<std::list<Zombie*>::iterator>>* 
		                                               poorman_heap = 
			new poorman_priority_queue<std::list<Zombie*>::iterator, 
                               compList<std::list<Zombie*>::iterator>>;
		return poorman_heap;
	}
	if(container == 3){
		compList<std::list<Zombie*>::iterator> comp(0);
		sorted_priority_queue<std::list<Zombie*>::iterator, 
                               compList<std::list<Zombie*>::iterator>>* 
							       sorted_heap = 
			new sorted_priority_queue<std::list<Zombie*>::iterator, 
                               compList<std::list<Zombie*>::iterator>>(comp);
		return sorted_heap;
	}

	else{
		sorted_priority_queue<std::list<Zombie*>::iterator, 
                               compList<std::list<Zombie*>::iterator>>* sorted_heap = 
			new sorted_priority_queue<std::list<Zombie*>::iterator, 
                               compList<std::list<Zombie*>::iterator>>;
		return sorted_heap;
		
		poorman_priority_queue<std::list<Zombie*>::iterator, 
                               compList<std::list<Zombie*>::iterator>>* 
							       poorman_heap = 
			new poorman_priority_queue<std::list<Zombie*>::iterator, 
                               compList<std::list<Zombie*>::iterator>>;
		return poorman_heap;
	}
}
*/
#endif
