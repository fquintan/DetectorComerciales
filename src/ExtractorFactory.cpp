#include "DescriptorExtractor.hpp"
#include "EdgeHistogramExtractor.hpp"
#include "GrayHistogramExtractor.hpp"
#include <stdlib.h> 
#include <stdexcept>

class ExtractorFactory{
public:
	ExtractorFactory(int w, int h): width(w), height(h){}

	DescriptorExtractor* createExtractor(std::vector<std::string> parameters){
		DescriptorExtractor* de;
		if (parameters[0] == "EDGE"){
			if (parameters.size() != 1) {
				throw std::invalid_argument("Not enough arguments");
			}
			EdgeHistogramExtractor *edge = new EdgeHistogramExtractor(height, width);
			de = edge;
		}
		else if (parameters[0] == "GRAY"){
			if (parameters.size() != 4) {
				throw std::invalid_argument("Not enough arguments");
			}
			int bins = std::stoi(parameters[1]);
			int vzones = std::stoi(parameters[2]);
			int hzones = std::stoi(parameters[3]);

			GrayHistogramExtractor *gray = new GrayHistogramExtractor(bins, width, height, vzones, hzones);
			de = gray;
		}
		else{
			throw std::invalid_argument("Not enough arguments");
		}
		return de;
	}

private:

	int width;
	int height;

};
