#include <string>
#include <vector>

std::vector<std::string> splitString(const std::string& str, const std::string &split) {
	std::vector<std::string> result;
	size_t start = 0;
	size_t end = str.find(split);
	while (end != std::string::npos) {
		result.push_back(str.substr(start, end - start));
		start = end + 1;
		end = str.find(split, start);
	}
	if (start < str.length()) {
		result.push_back(str.substr(start));
	}
	return result;
}