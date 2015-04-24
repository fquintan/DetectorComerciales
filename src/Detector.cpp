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

void writeMatchFound(std::ofstream &of, int indexStart, int indexEnd, int fps, std::string videoName){
	int startTime = (indexStart / fps);
	int endTime = (indexEnd / fps); 
	of << "vlc " << videoName << " --start-time " << startTime << " --stop-time " << endTime << " --repeat\n"; 
}

int loadBatch(std::vector<Descriptor> &v, int batchSize, std::ifstream* in){
	Descriptor* current;
	int count = 0;
	std::string descriptorAsString;
	std::string line;
	while (std::getline(*in, line)){
		    std::istringstream iss(line);
		    iss >> descriptorAsString;
		    current = new Descriptor(descriptorAsString);
		    v[count] = *current;
		    count++;
		    if(count >= batchSize){break;}
	}
	return count;
}


int main(int argc, char **argv) {

	/*System paramenters*/
	int FPS = 5;
	int BATCH_SIZE = 1000;
	int lengthThreshold = 10;

	std::ofstream output;
	std::string outName = argv[3];
	output.open(outName);
    
  

	std::string shortsDirName = argv[1];
	std::vector<std::string> filesShorts = Utils::getAllFilenames(shortsDirName);
	
	std::vector<Descriptor> descriptors;
	std::string descriptorAsString;
	Descriptor* current;
	std::string line;
	std::ifstream infile;
	for(std::string file : filesShorts){
		infile.open(file);
		while (std::getline(infile, line)){
		    std::istringstream iss(line);
		    iss >> descriptorAsString;
		    current = new Descriptor(descriptorAsString);
		    descriptors.push_back(*current);
		}
		infile.close();
		
	}
	std::cout << descriptors.size() << " descriptors loaded from shorts" <<  std::endl;
	std::string longVideoFile = argv[2];

	EuclideanComparator* comp;
	comp = new EuclideanComparator();
	BruteForceNNF nnf(descriptors, comp);
	infile.open(longVideoFile);

	int currentFoundIndex;
	int currentIndex = 0;
	int lastFoundIndex;
	int currentRunLength;

	int start = -2;
	bool reachedEndOfFile = false;
	int elementsLeft;
	int i;
	std::vector<Descriptor> longVideoDescriptors(BATCH_SIZE);
	while (!reachedEndOfFile) {
		elementsLeft = loadBatch(longVideoDescriptors, BATCH_SIZE, &infile);
		if (elementsLeft < BATCH_SIZE){
			reachedEndOfFile = true;
		}

		for(i = 0; i < elementsLeft; i++){
			currentIndex++;
			currentFoundIndex = nnf.find(&longVideoDescriptors[i]);
			if(currentFoundIndex == lastFoundIndex + 1){
				currentRunLength++;
			}
			else{
				if (currentRunLength >= lengthThreshold){
					writeMatchFound(output, start, currentIndex, FPS, longVideoFile);
				}
				start = currentIndex;
				currentRunLength = 0;
			}
			lastFoundIndex = currentFoundIndex;
		}
	}
	output.close();


}