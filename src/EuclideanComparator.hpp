#include "DescriptorComparator.hpp"

class EuclideanComparator : public DescriptorComparator{
public:
	EuclideanComparator();
	~EuclideanComparator();
	float compare(Descriptor* a, Descriptor* b);

};