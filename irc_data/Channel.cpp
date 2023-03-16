#include "Channel.hpp"

Channel::Channel(const string &name) : name(name) {

}

const User* Channel::getUser(int fd) const {
	map<int, User*>::const_iterator it = users.find(fd);
	if (it == users.end()) {
		throw out_of_range("User not found in channel.");
	}
	return (it->second);
}

void Channel::addUser(int fd, User *user) {
	users.insert(std::make_pair(fd, user));
}

const string &Channel::getName() const {
	return name;
}
