#ifndef USER_HPP
#define USER_HPP
#include <iostream>
#include <string>
using namespace std;

class User {
private:
	int fd;
	string nick;
	string username;
	string realName;
	bool authed;
public:
	void setNick(string &nick);
	const string &getUsername() const;
	void setUsername(const string &username);
	const string &getRealName() const;
	void setRealName(const string &realName);
	const string &getNick() const;

	User(int fd, bool authed) : fd(fd), authed(authed) {}
	int getFd() const;
	bool isAuthed() const;
};


#endif
