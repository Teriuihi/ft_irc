#include "Template.hpp"

const std::string &Template::getString() {
	result = str;
	for (size_t i = 0; i < placeholders.size(); i++) {
		size_t pos = 0;
		while ((pos = result.find(placeholders[i].getPlaceholder(), pos)) != std::string::npos) {
			result.replace(pos, placeholders[i].getPlaceholder().length(), placeholders[i].getReplacement());
			pos += placeholders[i].getReplacement().length();
		}
	}
	return result;
}

void Template::addPlaceholders(const Placeholder &placeholder) {
	bool set = false;
	for (size_t i = 0; i < placeholders.size(); i++) {
		if (placeholders[i].getPlaceholder() == placeholder.getPlaceholder()) {
			placeholders[i] = placeholder;
			set = true;
			break;
		}
	}
	if (!set)
		Template::placeholders.push_back(placeholder);
}
