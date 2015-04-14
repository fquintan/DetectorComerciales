#include "DescriptorExtractor.hpp"

class GrayHistogramExtractor : public DescriptorExtractor{
public:
	GrayHistogramExtractor(int bins);
	~GrayHistogramExtractor();
	Descriptor* extract(cv::Mat &image);
private:
	int bins;
/*	int zones_v;
	int zones_h;
	cv::Mat* masks;*/
};




