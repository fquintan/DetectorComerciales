#include <string>
#include <vector>
#include <sstream>

class Utils{
public:
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
};