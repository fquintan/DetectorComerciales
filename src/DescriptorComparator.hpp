#include <stdlib.h> 
#include "Descriptor.hpp"

#ifndef DESCRIPTORCOMPARATOR_H
#define DESCRIPTORCOMPARATOR_H

class DescriptorComparator{
public:
	/** returns a measure of disimilarity between two Descritors
		it assumes Descriptors of equal length*/
	virtual float compare(Descriptor* a, Descriptor* b)=0;
	virtual ~DescriptorComparator()=0;
};

#endif