#ifndef GUARD_source_h
#define GUARD_source_h

#include <iostream>
#include "order.h"

class Source{
public:	
	long long IDcount = 0;

	virtual ~Source() {};
	virtual bool empty() = 0;
	virtual Order* nextOrder() = 0;
	virtual void setup(std::istream&) = 0;
};

#endif
