#include "EuclideanComparator.hpp"


EuclideanComparator::EuclideanComparator(){}

EuclideanComparator::~EuclideanComparator(){}

float EuclideanComparator::compare(Descriptor* a, Descriptor* b){
	std::vector<float> vector_a = a->vector;
	std::vector<float> vector_b = b->vector; 
	int size = vector_a.size();
	int i;
	float distance = 0;
	for(i = 0; i < size; i++){
		float d = vector_a[i] - vector_b[i];
		d = d * d;
		distance += d;
	}
	return distance;
}