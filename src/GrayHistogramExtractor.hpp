#include "DescriptorExtractor.hpp"

class GrayHistogramExtractor : public DescriptorExtractor{
public:
	GrayHistogramExtractor(int bins, int h, int v, int vzones, int hzones);
	~GrayHistogramExtractor();
	Descriptor* extract(cv::Mat &image);
private:
	int bins;
	int zones_v;
	int zones_h;
	int height;
	int width;
	std::vector<cv::Mat> masks;
};




