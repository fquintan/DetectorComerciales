#include "ManhattanComparator.hpp"
#include <cmath>

#include <iostream>
#include <stdlib.h> 

ManhattanComparator::ManhattanComparator(){}

ManhattanComparator::~ManhattanComparator(){}

float ManhattanComparator::compare(Descriptor* a, Descriptor* b){
	std::vector<float> vector_a = a->vector;
	std::vector<float> vector_b = b->vector; 
	int size = vector_a.size();
	int i;
	float d;
	float distance = 0;
	for(i = 0; i < size; i++){
		// std::cout << vector_a[i] << "," << vector_b[i] << std::endl;
		d = vector_a[i] - vector_b[i];
		d = fabs(d);
		distance += d;
	}
	return distance;
}
