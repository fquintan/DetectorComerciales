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

  int FPS = 5;
  int skip = (30 / FPS) - 1;
  int j=0;
  int count = 0;
  
  std::ofstream myfile;
  std::string dirName = argv[1];
  cv::VideoCapture capture;
  std::vector<std::string> files = Utils::getAllFilenames(dirName);
  int numberOfFiles = files.size();
  for(std::string file : files){
    std::cout << file << std::endl;
  }
  int i;
  for (i = 0; i < numberOfFiles; i++){
    std::cout << "file: " << files[i] << std::endl;
    int end = 0;

    Utils::openVideo(capture, files[i]);

    cv::Mat frame, gray;
    DescriptorExtractor* extractor;
    Descriptor* current;

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
    std::string descriptorDirName = argv[3];
    std::string descriptorFilename = descriptorDirName + files[i] + ".des";
    myfile.open(descriptorFilename);
    std::cout << "opened " << descriptorFilename << std::endl;

    for (;;) {
      if (!capture.grab() || !capture.retrieve(frame)){
        break;
      }
      count++;
      if(count % 1000 == 0){
        std::cout << "Extracted " << count << " descriptors" << std::endl;
      }

      cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

      Descriptor* d;
      d = extractor->extract(gray);
      myfile << d->toString() << "\n";

      /*Skip a set amount of frames, it reaches the end, break*/
      for(j = 0;!end && j < skip; j++){
        if (!capture.grab() || !capture.retrieve(frame))
          end = 1;
      }
      if(end){break;}
    }

    myfile.close();
    std::cout << "Frame count: " << count << std::endl;
    delete factory;
    delete extractor;
  }
  
  return 0;
}
