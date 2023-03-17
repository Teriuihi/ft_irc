#include <sys/socket.h>
#include <vector>
#include "Channel.hpp"

Channel::Channel(const string &name) : name(name) {

}

const User* Channel::getUser(int fd) const {
	map<int, User*>::const_iterator it = users.find(fd);
	if (it == users.end()) {
		return NULL;
	}
	return (it->second);
}

void Channel::addUser(int fd, User *user) {
	users.insert(std::make_pair(fd, user));
}

void Channel::removeUser(int fd) {
	users.erase(fd);
}

const string &Channel::getName() const {
	return name;
}

void Channel::sendMessage(User *sender, const string& text) {
	const char *textToSend = text.c_str();
	size_t textLength = text.length();
	for (std::map<int, User*>::iterator it = users.begin(); it != users.end(); it++) {
		if (sender->getFd() == it->second->getFd())
			continue;
		send(it->second->getFd(), textToSend, textLength, 0);
	}
}
