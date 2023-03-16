#ifndef PLACEHOLDER_HPP
#define PLACEHOLDER_HPP
#include <string>

class Placeholder {
public:
	Placeholder(const std::string &placeholder, const std::string &str) : placeholder("<" + placeholder + ">"), replacement(str) {}
	const std::string &getPlaceholder() const { return placeholder; }
	const std::string &getReplacement() const { return replacement; }
private:
	std::string placeholder;
	std::string replacement;
};
#endif
