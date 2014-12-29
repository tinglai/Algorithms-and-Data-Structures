#pragma once
#include <vector>

// Do not modify this file, include it in problem4.cpp

struct Router {
	//Has value ’nullptr’ if this Router is the root
	Router* source;
	//Both of the following have value ‘nullptr’ if this
	//router is a leaf node
	Router* destination1;
	Router* destination2;
};

const Router* potentiallyBrokenRouter(const std::vector<const Router*>& routersReportingErrors);
