#include "Descriptor.hpp"
#include <stdlib.h> 
#include "DescriptorComparator.hpp"

#ifndef NEARESTNEIGHBORFINDER_H
#define NEARESTNEIGHBORFINDER_H


class NearestNeighborFinder {
public:
	virtual ~NearestNeighborFinder()=0;
	
	/*perform a nearest neighbor query over the dataset*/
	virtual int find(Descriptor* q)=0;

};

#endif