#include <iostream>
#include <stdlib.h> 
//#include "Descriptor.hpp"
#include "GrayHistogramExtractor.hpp"
#include "EdgeHistogramExtractor.hpp"
#include "EuclideanComparator.hpp"
#include "ManhattanComparator.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


int main(int argc, char **argv) {

  
  std::string filename = argv[1];
  cv::VideoCapture capture;
  std::cout << "abriendo video " << filename << std::endl;
  capture.open(filename);
  if (!capture.isOpened()) {
    std::cout << "abriendo camara " << filename << std::endl;
    int id_webcam = std::atoi(filename.c_str());
    capture.open(id_webcam);
  }
  if (!capture.isOpened()) {
    std::cout << "no puedo abrir " << filename << std::endl;
    return 1;
  }

  cv::Mat frame, gray;
  DescriptorExtractor* extractor;
  DescriptorComparator* comparator;
  comparator = new ManhattanComparator();
  std::string bins = argv[2];
  Descriptor* current;
  int skip = 23;
  int j=0;
  int end = 0;
  if (!capture.grab() || !capture.retrieve(frame))
    return 1;
  cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
  std::cout << "total: " << gray.cols << "," << gray.rows << std::endl;
  // extractor = new GrayHistogramExtractor(std::atoi(bins.c_str()), gray.cols, gray.rows, 2, 2);
  extractor = new EdgeHistogramExtractor(gray.rows, gray.cols);
  current = extractor->extract(gray);
  for (;;) {
  	for(j = 0;!end && j < skip; j++){
	    if (!capture.grab() || !capture.retrieve(frame))
	      end = 1;
  	}
  	if(end){return 0;}
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    Descriptor* d;
    d = extractor->extract(gray);
    float distance = comparator->compare(current, d);
    std::cout << distance << std::endl;
	delete current;
	current = d;
  }
  delete extractor;
  return 0;
}