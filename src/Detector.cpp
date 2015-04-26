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
	std::string name = "videos/mega-2014_04_20T21_59_53.mp4";
	of << "comercial " << videoName << "\n"; 
	of << "vlc " << name << " --start-time " << startTime << " --stop-time " << endTime << " --repeat\n"; 
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

int identifyComercial(std::vector<int> shorts, int d){
	int i = -1;
	for(int c : shorts){
		if (d < c){
			return i;
		}
		i++;
	}
	return i;
}

int main(int argc, char **argv) {

	/*System paramenters*/
	int FPS = 5;
	int BATCH_SIZE = 1000;
	int lengthThreshold = 20;
	float distanceThreshold = 0.001;
	int limit = std::stoi(argv[4]);

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
	std::vector<int> comercials;
	std::vector<int> comercialLengths;
	std::vector<std::string> comercialNames;
	int i = 0;
	for(std::string file : filesShorts){
		comercialNames.push_back(file);
		infile.open(file);
		comercials.push_back(i);
		while (std::getline(infile, line)){
			i++;
		    std::istringstream iss(line);
		    iss >> descriptorAsString;
		    current = new Descriptor(descriptorAsString);
		    descriptors.push_back(*current);
		}
		comercialLengths.push_back((i - comercials.back()));
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
	int currentRunLength = 0;

	int start = -2;
	bool reachedEndOfFile = false;
	int elementsLeft;
	int count = 0;
	int lastComercial = -1; 
	int currentComercial;
	float distance;
	std::vector<Descriptor> longVideoDescriptors(BATCH_SIZE);
	while (!reachedEndOfFile) {
		elementsLeft = loadBatch(longVideoDescriptors, BATCH_SIZE, &infile);
		if (elementsLeft < BATCH_SIZE){
			reachedEndOfFile = true;
		}

		for(i = 0; i < elementsLeft; i++){
			currentIndex++;
			currentFoundIndex = nnf.find(&longVideoDescriptors[i]);
			distance = comp->compare(&longVideoDescriptors[i], &descriptors[currentFoundIndex]);
			if(distance <= distanceThreshold){
				currentComercial = identifyComercial(comercials, currentFoundIndex);
			}
			else{
				currentComercial = -1;
			}
			if(currentComercial == lastComercial && currentComercial != -1){
				currentRunLength++;
			}
			else{
				if ( lastComercial != -1 && currentRunLength >= (comercialLengths[lastComercial] * 0.8) ){
					writeMatchFound(output, start, currentIndex, FPS, comercialNames[lastComercial]);
				}
				start = currentIndex;
				currentRunLength = 0;
			}
			lastComercial = currentComercial;
		}
		count += elementsLeft;
		std::cout << "Analized " << count << " descriptors" << std::endl;
		if(count >= limit){
			reachedEndOfFile = true;
		}
	}
	output.close();


}