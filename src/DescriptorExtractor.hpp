#include <stdlib.h> 
#include "Descriptor.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#ifndef DESCRIPTOREXTRACTOR_H
#define DESCRIPTOREXTRACTOR_H
//Place the abstract class here

class DescriptorExtractor{
public:
	/** Receives a matrix representation of a gray image
		and returns a Descriptor for that image*/
	virtual Descriptor* extract(cv::Mat &image)=0;
	virtual ~DescriptorExtractor()=0;
};


#endif