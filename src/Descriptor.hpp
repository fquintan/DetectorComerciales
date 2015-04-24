#include <stdlib.h> 
#include <vector>
#include <string>


#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

class Descriptor{


public:
	Descriptor();
	Descriptor(std::vector<float> v);
	Descriptor(std::string s);
	~Descriptor();
	std::string toString();

	std::vector<float> vector;
};

#endif