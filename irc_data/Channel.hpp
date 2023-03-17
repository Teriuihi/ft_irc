#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include "User.hpp"
#include <map>

class Channel {
private:
	string name;
	map<int, User*> users;
public:
	Channel(const string &name);
	const User* getUser(int fd) const;
	void addUser(int fd, User *user);
	const string &getName() const;
	void sendMessage(User *sender, const string& text);
};
#endif
