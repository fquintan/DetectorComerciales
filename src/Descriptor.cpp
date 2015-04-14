#include "Descriptor.hpp"
#include <sstream>
#include <stdlib.h> 


/**
	Represents a descriptor as a float vector
*/

Descriptor::Descriptor(std::vector<float> v): vector(v){}
Descriptor::~Descriptor(){}

std::string Descriptor::toString(){
	int size = vector.size();
	int i;

	std::stringstream ss;

	for(i = 0; i < size - 1; i++){
	//put arbitrary formatted data into the stream
		ss << vector[i] << ",";
	}
	ss << vector[size - 1];// << std::endl;
	//convert the stream buffer into a string
	std::string str = ss.str();
	return str;
}
