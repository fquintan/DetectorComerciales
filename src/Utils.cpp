#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <stdexcept>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#include <fcntl.h>

class Utils{
public:

	static int openVideo(cv::VideoCapture &capture, std::string filename){
		std::cout << "abriendo video " << filename << std::endl;
		capture.open(filename);
		if (!capture.isOpened()) {
			std::cout << "abriendo camara " << filename << std::endl;
			int id_webcam = std::atoi(filename.c_str());
			capture.open(id_webcam);
		}
		if (!capture.isOpened()) {
			// std::cout << "no puedo abrir " << filename << std::endl;
			return 0;
		}
			return 1;
		}
	static std::vector<std::string> split(std::string string, const char delim) {
		std::vector<std::string> elems;
		std::stringstream ss(string);
		std::string item;
		while (std::getline(ss, item, delim)) {
			if (!item.empty())
				elems.push_back(item);
		}
		return elems;
	}

	static bool existsFile(std::string filename) {
		struct stat st;
		if (stat(filename.c_str(), &st) == 0)
			return S_ISREG(st.st_mode) ? true : false;
		return false;
	}

	static std::vector<std::string> getAllElementsInDir(std::string path) {
		std::vector<std::string> list;
	#if _WIN32
		DIR *dp = opendir(path.c_str());
		if (dp == NULL)
			throw std::runtime_error("can't open " + path);
		struct dirent *dir_entry;
		while ((dir_entry = readdir(dp)) != NULL) {
			char *name = dir_entry->d_name;
			list.push_back(std::string(name));
		}
		closedir(dp);
	#elif __linux
		struct dirent **namelist = NULL;
		int len = scandir(path.c_str(), &namelist, NULL, alphasort);
		if (len < 0)
			throw std::runtime_error("can't open " + path);
		for (int i = 0; i < len; ++i) {
			char *name = namelist[i]->d_name;
			list.push_back(std::string(name));
			free(namelist[i]);
		}
		free(namelist);
	#endif
		return list;
	}
	
	static std::vector<std::string> getAllFilenames(std::string path) {
		std::vector<std::string> list = getAllElementsInDir(path);
		std::vector<std::string> file_list;
		for (std::string fname : list) {
			if (fname.compare(0, 1, ".") == 0) //archivos que comienzan por "."
				continue;
			std::string full_name = path + "/" + fname;
			if (existsFile(full_name))
				file_list.push_back(full_name);
		}
		return file_list;
	}

};