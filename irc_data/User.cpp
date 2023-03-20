#include "User.hpp"

int User::getFd() const {
	return fd;
}

const string &User::getNick() const {
	return nick;
}

void User::setNick(string &nick) {
	User::nick = nick;
}

const string &User::getUsername() const {
	return username;
}

void User::setUsername(const string &username) {
	User::username = username;
}

const string &User::getRealName() const {
	return realName;
}

void User::setRealName(const string &realName) {
	User::realName = realName;
}

const string &User::getHostname() const {
	return hostname;
}

void User::setHostname(const string &hostname) {
	User::hostname = hostname;
}

const string &User::getServername() const {
	return servername;
}

void User::setServername(const string &servername) {
	User::servername = servername;
}

bool User::isServerOp() const {
	return serverOp;
}

void User::setServerOp(bool serverOp) {
	User::serverOp = serverOp;
}
