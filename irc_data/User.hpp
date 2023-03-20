#ifndef USER_HPP
#define USER_HPP
#include <iostream>
#include <string>
using namespace std;

class User { //TODO have a check for if someone has everything they need to have set set before they can do other stuff
private:
	int fd;
	string nick;
	string username;
	string realName;
	string hostname;
	string servername;
	bool serverOp;
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

	bool isServerOp() const;

	void setServerOp(bool serverOp);

	User(int fd) : fd(fd) {}
	int getFd() const;
};


#endif
