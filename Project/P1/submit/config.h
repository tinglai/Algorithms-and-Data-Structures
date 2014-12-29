#ifndef GUARD_config_h
#define GUARD_config_h

class Config{
private:
	bool isRouteQueue;
	//isRouteQueue = 1 route using queue
	//isRouteQueue = 0 route using stack
	bool isOutputMap;
	//isOutputMap = 1 output by map
	//isOutputMap = 0 output by list
public:
	Config();
	int get_RouteConfig();
	int get_OutputConfig();
	void setup(int, char *const*);
};

#endif
