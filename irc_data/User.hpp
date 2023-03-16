#ifndef USER_HPP
#define USER_HPP
#include <iostream>
#include <string>
using namespace std;

class User {
private:
	int fd;
	string nick;
	bool authed;
public:
	void setNick(string &nick);

	User(int fd, bool authed) : fd(fd), authed(authed) {}
	int getFd() const;
	bool isAuthed() const;
	const string &getNick() const;
};


#endif
