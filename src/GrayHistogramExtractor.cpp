#include "GrayHistogramExtractor.hpp"
#include <iostream>

GrayHistogramExtractor::GrayHistogramExtractor(int numberOfBins, int w, int h, int vzones, int hzones):
 bins(numberOfBins), zones_v(vzones), zones_h(hzones), height(h), width(w){
 	// std::cout << "constructor"<< std::endl;
	int zonas = zones_h * zones_v;
	std::vector<cv::Mat> mascaras(zonas);
	masks = mascaras;
	cv::Mat mask;
	int i, j;
	int x = 0;
	int delta_h = width / zones_h;
	int delta_v = height / zones_v;
	// std::cout << "w,h: "<< width << "," << height << std::endl;
	// std::cout << "zones h,v : "<< zones_h << "," << zones_v << std::endl;
	// std::cout << "deltax,y: "<< delta_h << "," << delta_v << std::endl;

	for (i = 0; i < zones_h; i++){
		int y = 0;
		for (j = 0; j < zones_v; j++){
			// std::cout << "x, x+delta: "<< x << ", " << x+delta_h << std::endl;
			// std::cout << "y, y+delta: "<< y << ", " << y+delta_v << std::endl;
			mask = cv::Mat::zeros(height, width, CV_8U); // all 0
			mask(cv::Rect(x, y, delta_h, delta_v)) = 1;
			y += delta_v;
			// std::cout << "index: "<< (i*zones_v + j) << std::endl;
			masks[i*zones_v + j] = mask;
			// mask.copyTo(masks[i*zones_h + j]);
		}
		x += delta_h;
	}
	// std::cout << "extractor w,h: " << width << "," << height << std::endl;
}

GrayHistogramExtractor::~GrayHistogramExtractor(){}

Descriptor* GrayHistogramExtractor::extract(cv::Mat &image){
	// std::cout << "extract"<< std::endl;
	
	int cols = image.cols;
	int rows = image.rows;
	float total = (float) cols * rows;
    int histSize[] = {bins};
	int i, j;
    float range[] = { 0, 256 };
    const float* ranges[] = { range };
    cv::Mat hist;
    int channels[] = { 0 };
	int zones = zones_h * zones_v;
	std::vector<float> f_hist(bins * zones, 0.0);

    for (j = 0; j < zones; j++){
	    cv::calcHist( &image, 1, channels, masks[j], // do not use mask
	             hist, 1, histSize, ranges,
	             true, // the histogram is uniform
	             false );
	    //Normalize
		for (i = 0; i < bins; i++){
			f_hist[i + j*bins] = hist.at<float>(i)/total;
		}
    }

	Descriptor* d = new Descriptor(f_hist);
	return d;
}


