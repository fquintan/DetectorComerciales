#include "DescriptorComparator.hpp"

class ManhattanComparator : public DescriptorComparator{
public:
	ManhattanComparator();
	~ManhattanComparator();
	float compare(Descriptor* a, Descriptor* b);

};