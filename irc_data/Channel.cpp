#include <sys/socket.h>
#include <vector>
#include <sstream>
#include "Channel.hpp"

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

void Channel::broadcastMessage(const string &text) {
	const char *textToSend = text.c_str();
	size_t textLength = text.length();
	for (std::map<int, User*>::iterator it = users.begin(); it != users.end(); it++) {
		send(it->second->getFd(), textToSend, textLength, 0);
	}
}

const string &Channel::getTopic() const {
	return topic;
}

void Channel::setTopic(const string &newTopic) {
	this->topic = newTopic;
}

Channel::Channel(const string &name, const string &topic) : name(name), topic(topic) {}

std::string Channel::getUserList() {
	std::string userList;
	std::map<int, User*>::iterator it;
	for (it = users.begin(); it != users.end(); ++it) {
		if (!userList.empty())
			userList += " ";
		User* user = it->second;
		userList += "+" + user->getUsername();
	}
	return userList;
}

std::string Channel::getUserCount() {
	std::ostringstream oStringStream;
	oStringStream << users.size();
	return oStringStream.str();
}

bool Channel::isOp(User *user) {
	for (vector<User *>::iterator it = opList.begin(); it != opList.end(); ++it) {
		if (*it == user) {
			return true;
		}
	}
	return false;
}

void Channel::addOp(User *user) {
	if (isOp(user))
		return;
	opList.push_back(user);
}

void Channel::removeOp(User *user) {
	vector<User *>::iterator it = opList.begin();
	while (it != opList.end()) {
		if (*it == user) {
			it = opList.erase(it);
		} else {
			++it;
		}
	}
}
