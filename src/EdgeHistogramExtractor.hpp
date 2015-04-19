#include "DescriptorExtractor.hpp"

class EdgeHistogramExtractor : public DescriptorExtractor{
public:
	EdgeHistogramExtractor(int h, int w);
	~EdgeHistogramExtractor();
	Descriptor* extract(cv::Mat &image);
private:
	int heigth;
	int width;
	int imageBlockSize;
	std::vector<cv::Mat> filters;
	int threshold;

	/*Takes a matrix block and computes its intensity as the sum of the values of its elements*/
	float computeIntensity(cv::Mat &block);
	/*Takes a vector of intensities if the maximum intensity exceeds a threshold it is added to the histogram in its corresponding position*/
	void addToHistogram(std::vector<float> intensities,  float threshold, std::vector<int> &histogram);
	/*Computes the edge histogram for an image sector defined by the given coordinates*/
	std::vector<int> extractSectorHistogram(cv::Mat &image, int start_x, int start_y, int end_x, int end_y);
};




