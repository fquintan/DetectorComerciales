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
	int startTime = (int)(indexStart / 4.995);
	int endTime = (int)(indexEnd / 4.995); 
	std::string name = "videos/mega-2014_04_20T21_59_53.mp4";
	of << "comercial " << videoName << " #### "; 
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
	float distanceThreshold = 0.002;
	int toleratedFailures = 2;
	int limit = std::stoi(argv[4]);

	/*File to write results*/
	std::ofstream output;
	std::string outName = argv[3];
	output.open(outName);
    
  
	/*Files containing the comercial's descriptors*/
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

	/*Initializing the nearest neighbor finder*/
	EuclideanComparator* comp;
	comp = new EuclideanComparator();
	BruteForceNNF nnf(descriptors, comp);
	infile.open(longVideoFile);

	std::vector<int> nearestComercials;
	std::vector<Descriptor> longVideoDescriptors(BATCH_SIZE);

	float distance;
	int elementsLeft;
	int nearestIndex;
	bool reachedEndOfFile = false;
	int currentComercial;
	int count = 0;
	
	/*
	For every descriptor in the long file find the index of the nearest comercial frame
	if that frame is close enough, the id of the corresponding comercial is saved
	otherwise save -1
	*/
	std::cout << "Computing nearest neighbors for all descriptors" << std::endl;

	while (!reachedEndOfFile) {
		elementsLeft = loadBatch(longVideoDescriptors, BATCH_SIZE, &infile);
		if (elementsLeft < BATCH_SIZE){
			reachedEndOfFile = true;
		}
		for(i = 0; i < elementsLeft; i++){
			nearestIndex = nnf.find(&longVideoDescriptors[i]);
			distance = comp->compare(&longVideoDescriptors[i], &descriptors[nearestIndex]);
			if(distance <= distanceThreshold){
				currentComercial = identifyComercial(comercials, nearestIndex);
			}
			else{
				currentComercial = -1;
			}
			// std::cerr << currentComercial << std::endl;
			nearestComercials.push_back(currentComercial);
		}
		count += elementsLeft;
		std::cout << count << " Descriptors analyzed" << std::endl;
		if(count >= limit){
			reachedEndOfFile = true;
		}
	}

	/*Finished computing nearest neighbors now we examine the matches to find comercials*/

	int failures = 0;
	int lastComercial = -1;
	int currentComercialLength = 0;
	bool currentlyInsideRun = false;
	int startIndex;
	int currentIndex = 0;
	int comercialsFound = 0;

	std::cout << "Searching for matching comercials" << std::endl;

	for(int current : nearestComercials){
		if(currentlyInsideRun){
			if(current != lastComercial){
				failures++;
				if(failures > toleratedFailures){
					/*check if the current run length is at least 90% of the corresponding comercial*/
					currentComercialLength = currentIndex - startIndex;
					if(currentComercialLength >= comercialLengths[lastComercial] * 0.9){
						/*Write the result to file, otherwise discard run and continue*/
						writeMatchFound(output, startIndex, currentIndex, FPS, comercialNames[lastComercial]);
						comercialsFound++;
						currentlyInsideRun = false;
						failures = 0;

					}
					else{
						currentlyInsideRun = false;
						failures = 0;
					}
				}
			}
			else{
			/*if the current comercial is the same as before reset the failure counter and continue the current run*/
				failures = 0;
			}
		}
		else{
			if(current != -1){
				lastComercial = current;
				failures = 0;
				startIndex = currentIndex;
				currentlyInsideRun = true;
			}
		}
		currentIndex++;
		if(currentIndex % 1000 == 0){
			std::cout << "Analyzed " << currentIndex << " frames, comercials found: " << comercialsFound << std::endl;
		}
	}

	output.close();


}