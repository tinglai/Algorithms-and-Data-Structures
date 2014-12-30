#ifndef GUARD_config_h
#define GUARD_config_h

#include<vector>
#include<iostream>

class Config{
private:
	bool isMSet = false;
public:
	char mode;

	Config(){}
	void setup(int, char *const*);
};

#endif
