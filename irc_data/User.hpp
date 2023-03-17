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
	string hostname;
	string servername;
	bool authed;
public:
	void setNick(string &nick);
	const string &getUsername() const;
	void setUsername(const string &username);
	const string &getRealName() const;
	void setRealName(const string &realName);
	const string &getNick() const;

	const string &getHostname() const;

	void setHostname(const string &hostname);

	const string &getServername() const;

	void setServername(const string &servername);

	User(int fd, bool authed) : fd(fd), authed(authed) {}
	int getFd() const;
	bool isAuthed() const;
};


#endif
