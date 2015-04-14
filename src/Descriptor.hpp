#include <stdlib.h> 
#include <vector>
#include <string>


#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

class Descriptor{


public:
	Descriptor(std::vector<float> v);
	~Descriptor();
	std::string toString();

	std::vector<float> vector;
};

#endif