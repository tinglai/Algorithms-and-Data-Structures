#ifndef GUARD_config_h
#define GUARD_config_h
#include <string>

class Config{
private:
	int container;
	std::string arrow;
	unsigned int v;
	bool de; //for debug mode
	std::string fileName;
public:
	Config();
	int getContainer();
	std::string getArrow() const;
	unsigned int getV();
	bool getDe() const;
	void setup(int, char *const*);
	std::string getFileName();
};

#endif
