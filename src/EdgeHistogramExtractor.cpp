#include "EdgeHistogramExtractor.hpp"
#include <iostream>

EdgeHistogramExtractor::EdgeHistogramExtractor(int h, int w) : heigth(h), width(w){
	std::vector<cv::Mat> filtros(5);
	filtros[0] = (cv::Mat_<uchar>(2,2) << 1 , -1, 1, -1);
	filtros[1] = (cv::Mat_<uchar>(2,2) << 1 , 1, -1, -1);
	filtros[2] = (cv::Mat_<float>(2,2) << 1.414213 , 0, -1.414213, 0);
	filtros[3] = (cv::Mat_<float>(2,2) << 0 , 1.414213, -1.414213, 0);
	filtros[4] = (cv::Mat_<uchar>(2,2) << 2 , -2, 2, -2);

	filters = filtros;
	imageBlockSize = 4;
	threshold = 0.0;
}

EdgeHistogramExtractor::~EdgeHistogramExtractor(){}

Descriptor* EdgeHistogramExtractor::extract(cv::Mat &image){

	int n_filters = filters.size();
	int histSize = n_filters * 16;
	std::vector<int> histogram(histSize);
	std::vector<float> f_histogram(histSize);
	std::vector<int> currentSectorHistogram;
	
	int delta_x = width / 4;
	int delta_y = heigth / 4;
	int i, j;
	/*Compute histogram for each sector and concatenate them into a single vector*/
	for(i = 0; i + delta_x < width; i += delta_x){
		for(j = 0; j + delta_y < heigth; j += delta_y){
			currentSectorHistogram = extractSectorHistogram(image, i, j, i + delta_x, j + delta_y);
			histogram.insert( histogram.end(), currentSectorHistogram.begin(), currentSectorHistogram.end());
		}
	}
	/*Normalize the histogram and return descriptor*/
	int count = 0;
	for(i = 0; i < histSize; i++){
		count += histogram[i];
	}
	for(i = 0; i < histSize; i++){
		f_histogram[i] = ((float) histogram[i]) / count;
	}
	Descriptor* d = new Descriptor(f_histogram);
	return d;
}

std::vector<int> EdgeHistogramExtractor::extractSectorHistogram(cv::Mat &image, int start_x, int start_y, int end_x, int end_y){
	int n_filters = filters.size();
	std::vector<float> intensities(n_filters);
	cv::Mat currentBlock, convResult;
	std::vector<int> histogram(0, n_filters);

	int i, j, k;
	for(i = start_x; i + imageBlockSize < end_x; i += imageBlockSize){
		for(j = start_y; j + imageBlockSize < end_y; j += imageBlockSize){
	    	currentBlock = image(cv::Rect(10, 10, 100, 100));
	    	for(k = 0; k < n_filters; k++){
			    cv::filter2D(currentBlock, convResult, -1 , filters[k], cv::Point( -1, -1 ), 0, cv::BORDER_DEFAULT);
			    intensities[k] = computeIntensity(convResult);
	    	}
	    	addToHistogram(intensities, threshold, histogram);
		}
	}
	return histogram;
}

float EdgeHistogramExtractor::computeIntensity(cv::Mat &block){
	float intensity = 0;
	int rows = block.rows;
	int cols = block.cols;
	int i, j;
	for(i = 0; i < rows; i++){
		for (j = 0; i < cols; j++){
			intensity += block.at<float>(i, j);
		}
	}
	return intensity;
}
void EdgeHistogramExtractor::addToHistogram(std::vector<float> intensities, float threshold, std::vector<int> &histogram){
	auto max = std::max_element(std::begin(intensities), std::end(intensities));
	if(*max >= threshold){
		int index = std::distance(std::begin(intensities), max);
		histogram[index]++;
	}
}
