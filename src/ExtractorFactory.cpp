#include "DescriptorExtractor.hpp"
#include "EdgeHistogramExtractor.hpp"
#include "GrayHistogramExtractor.hpp"
#include <stdlib.h> 
#include <stdexcept>

class ExtractorFactory{
public:
	ExtractorFactory(){}

	DescriptorExtractor* createExtractor(std::vector<std::string> parameters){
		DescriptorExtractor* de;
		if (parameters[0] == "EDGE"){
			if (parameters.size() != 3) {
				throw std::invalid_argument("Not enough arguments");
			}
			int a = std::stoi(parameters[1]);
			int b = std::stoi(parameters[2]);
			EdgeHistogramExtractor *edge = new EdgeHistogramExtractor(a, b);
			de = edge;
		}
		else if (parameters[0] == "GRAY"){
			if (parameters.size() != 6) {
				throw std::invalid_argument("Not enough arguments");
			}
			int bins = std::stoi(parameters[1]);
			int w = std::stoi(parameters[2]);
			int h = std::stoi(parameters[3]);
			int vzones = std::stoi(parameters[4]);
			int hzones = std::stoi(parameters[5]);
			GrayHistogramExtractor *gray = new GrayHistogramExtractor(bins, w, h, vzones, hzones);
			de = gray;
		}
		else{
			throw std::invalid_argument("Not enough arguments");
		}

		return de;
	}	
};