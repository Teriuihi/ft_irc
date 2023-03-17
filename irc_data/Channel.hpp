#ifndef CHANNEL_HPP
#define CHANNEL_HPP
#include "User.hpp"
#include <map>

class Channel {
private:
	string name;
	string topic;
	map<int, User*> users;
public:
	Channel(const string &name, const string &topic);
	const User* getUser(int fd) const;
	void addUser(int fd, User *user);
	const string &getName() const;
	void sendMessage(User *sender, const string& text);
	void removeUser(int fd);
	const string &getTopic() const;
	void setTopic(const string &newTopic);
	std::string getUserList();
	std::string getUserCount();
};
#endif
