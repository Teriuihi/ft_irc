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

std::string joinString(std::vector<std::string> &split, const std::string &separator, int skip) {
	std::string result;
	for (std::vector<std::string>::iterator it = split.begin(); it != split.end(); ++it) {
		if (skip != 0) {
			skip--;
			continue;
		}
		if (it != split.begin() + 1) {
			result += separator;
		}
		result += *it;
	}
	return result;
}