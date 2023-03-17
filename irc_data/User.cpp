#include "User.hpp"

int User::getFd() const {
	return fd;
}

const string &User::getNick() const {
	return nick;
}

bool User::isAuthed() const {
	return authed;
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
