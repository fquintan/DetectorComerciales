#include <iostream>
#include <stdlib.h> 
//#include "Descriptor.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <fstream>
#include "Utils.cpp"
#include "Descriptor.hpp"
#include "BruteForceNNF.hpp"
#include "EuclideanComparator.hpp"
#include "ExtractorFactory.cpp"


int main(int argc, char **argv) {
	std::cout << "holi" <<  std::endl;

	int FPS = 5;
	int skip = (30 / FPS) - 1;

	std::string dirName = argv[1];
	std::vector<std::string> files = Utils::getAllFilenames(dirName);
	
	std::vector<Descriptor> descriptors;
	std::string descriptorAsString;
	Descriptor* current;
	std::string line;
	for(std::string file : files){
		std::ifstream infile(file);
		while (std::getline(infile, line)){
		    std::istringstream iss(line);
		    iss >> descriptorAsString;
		    current = new Descriptor(descriptorAsString);
		    descriptors.push_back(*current);
		}
	}
	std::cout << descriptors.size() << " descriptors loaded" <<  std::endl;
	EuclideanComparator* comp;
	comp = new EuclideanComparator();
	BruteForceNNF nnf(descriptors, comp);

    std::vector<std::string> parameters;
    parameters = Utils::split(argv[3], '_'); 

	cv::Mat frame, gray;
	cv::VideoCapture capture;
  	std::string filename = argv[2];
	Utils::openVideo(capture, filename);
	if (!capture.grab() || !capture.retrieve(frame)){
			return 1;
	}
	int width = frame.cols;
	int height = frame.rows;

	DescriptorExtractor* extractor;
	ExtractorFactory* factory = new ExtractorFactory(width, height); 
    extractor = factory->createExtractor(parameters);

	int foundIndex;
	int end = 0;
	int j;
	for (;;) {
		if (!capture.grab() || !capture.retrieve(frame)){
			break;
		}
		cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

		Descriptor* d;
		d = extractor->extract(gray);

		foundIndex = nnf.find(d);
		std::cout << "found index: " << foundIndex << std::endl; 
		/*Skip a set amount of frames, it reaches the end, break*/
		for(j = 0;!end && j < skip; j++){
			if (!capture.grab() || !capture.retrieve(frame))
			end = 1;
		}
		if(end){break;}
	}

}