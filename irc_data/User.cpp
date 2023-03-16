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
