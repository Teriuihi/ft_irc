#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include <vector>
#include "Placeholder.hpp"

class Template {
public:
	Template(const std::string& str) : str(str), placeholders() {}
	void addPlaceholders(const Placeholder &placeholder);
	const std::string& getString();
private:
	std::string str;
	std::string result;
	std::vector<Placeholder> placeholders;
};


#endif
