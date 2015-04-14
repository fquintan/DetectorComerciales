#include "GrayHistogramExtractor.hpp"
#include <iostream>

GrayHistogramExtractor::GrayHistogramExtractor(int numberOfBins): bins(numberOfBins){}

GrayHistogramExtractor::~GrayHistogramExtractor(){}

Descriptor* GrayHistogramExtractor::extract(cv::Mat &image){
	int cols = image.cols;
	int rows = image.rows;
	float total = (float) cols * rows;
    int histSize[] = {bins};
	int i;
    float range[] = { 0, 256 };
    const float* ranges[] = { range };
    cv::Mat hist;
    int channels[] = { 0 };
    cv::calcHist( &image, 1, channels, cv::Mat(), // do not use mask
             hist, 1, histSize, ranges,
             true, // the histogram is uniform
             false );
    //Normalize
	std::vector<float> f_hist(bins, 0.0);
	for (i = 0; i < bins; i++){
		f_hist[i] = hist.at<float>(i)/total;
	}

	Descriptor* d = new Descriptor(f_hist);
	return d;
}


