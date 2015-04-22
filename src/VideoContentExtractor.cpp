#include <iostream>
#include <stdlib.h> 
//#include "Descriptor.hpp"
#include "Utils.cpp"
#include "ExtractorFactory.cpp"
#include "EuclideanComparator.hpp"
#include "ManhattanComparator.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>


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
  // std::string bins = argv[2];
  Descriptor* current;
  int FPS = 5;
  int skip = (30 / FPS) - 1;
  int j=0;
  int end = 0;
  int count = 0;

  /*Need the first image to create the descriptor extractor*/  
  if (!capture.grab() || !capture.retrieve(frame)){
    return 1;
  }
  count++;
  cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

  int height = gray.rows;
  int width = gray.cols;

  std::vector<std::string> parameters;
  parameters = Utils::split(argv[2], '_'); 
  ExtractorFactory* factory = new ExtractorFactory(width, height); 
  std::cout << "w,h: " << width << "," << height << std::endl;
  // extractor = new GrayHistogramExtractor(std::atoi(bins.c_str()), gray.cols, gray.rows, 2, 2);
  // extractor = new EdgeHistogramExtractor(gray.rows, gray.cols);
  extractor = factory->createExtractor(parameters);
  std::ofstream myfile;
  myfile.open ("example.txt");
  
  /*For test only, not needed in the actual program*/
  current = extractor->extract(gray);
  for (;;) {
    if (!capture.grab() || !capture.retrieve(frame))
    return 1;
    count++;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    Descriptor* d;
    d = extractor->extract(gray);
    myfile << d->toString() << "\n";
 //  float distance = comparator->compare(current, d);
   //  std::cout << distance << std::endl;
    // delete current;
    // current = d;

    /*Skip a set amount of frames, it reaches the end, break*/
    for(j = 0;!end && j < skip; j++){
      if (!capture.grab() || !capture.retrieve(frame))
        end = 1;
      count++;
    }
    if(end){break;}
  }

  myfile.close();
  std::cout << "Frame count: " << count << std::endl;
  
  delete extractor;
  delete factory;
  return 0;
}