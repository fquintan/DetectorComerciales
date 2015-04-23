#include "NearestNeighborFinder.hpp"
#include "Descriptor.hpp"
#include "DescriptorComparator.hpp"


class BruteForceNNF: public NearestNeighborFinder{

public:
	BruteForceNNF(std::vector<Descriptor> d, DescriptorComparator* comp);
	~BruteForceNNF();
	int find(Descriptor* q);

private:
	std::vector<Descriptor> descriptors;
	DescriptorComparator* comparator;

};