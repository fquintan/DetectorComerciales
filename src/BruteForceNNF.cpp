#include "BruteForceNNF.hpp"


BruteForceNNF::BruteForceNNF(std::vector<Descriptor> d, DescriptorComparator* comp) :
 descriptors(d), comparator(comp){}

BruteForceNNF::~BruteForceNNF(){}


int BruteForceNNF::find(Descriptor* q){
	float minDistance = 10000.0;
	float currentDistance;
	// Descriptor* nn;
	int i;
	int size = descriptors.size();
	int index = 0;
	for(i = 0; i < size; i++){
		currentDistance = comparator->compare(q, &descriptors[i]);
		if (currentDistance < minDistance){
			minDistance = currentDistance;
			index = i;
		}

	}
	return index;
}