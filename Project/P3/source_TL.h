#ifndef GUARD_source_TL_h
#define GUARD_source_TL_h

#include "source.h"
#include <iostream>
#include "order.h"
#include <string>

class Source_TL: public Source{
public:
	Source_TL(){};
	void setup(std::istream&);
	bool empty();
	Order* nextOrder();
private:
	std::istream* readin;
};

#endif
