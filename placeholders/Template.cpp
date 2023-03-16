#include "Template.hpp"

const std::string &Template::getString() {
	for (size_t i = 0; i < placeholders.size(); i++) {
		size_t pos = 0;
		while ((pos = str.find(placeholders[i].getPlaceholder(), pos)) != std::string::npos) {
			str.replace(pos, placeholders[i].getPlaceholder().length(), placeholders[i].getReplacement());
			pos += placeholders[i].getReplacement().length();
		}
	}
	return str;
}

void Template::addPlaceholders(const Placeholder &placeholder) {
	Template::placeholders.push_back(placeholder);
}
