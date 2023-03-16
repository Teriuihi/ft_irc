#ifndef SERVER_HPP
#define SERVER_HPP
#include <netinet/in.h>
#include <iostream>
#include <unistd.h>
#include <poll.h>
#include <vector>
#include "Channel.hpp"
#include "../BST/BSTree.hpp"
#include "../commands/CommandHandler.hpp"
#include "../helper_files/static_variables.hpp"
#include "../helper_files/badFixHeader.hpp"

class Server {
public:
	Server(int port, const string &password);
	int getSockFd() const { return sockFd; }
	const sockaddr_in &getServAddr() const { return serv_addr; }
	pollfd *getPollFd() { return pollFd; }
	void removeUser(int fd) { activeUsers.remove(fd); }
	void addUser(int fd, User *user) { activeUsers.insert(fd, (void *)user); }
	User* getUser(int fd) { return (User *) activeUsers.getNode(fd)->getValue(); }

	std::string getPassword() { return password; }
	void forwardMessage(char *message);
	void receivedMessage(char *message, int fd);
	void closeServer() const;
	Channel* getChannel(const string& name);

private:
	int sockFd;
	std::string password;
	struct sockaddr_in serv_addr;
	struct pollfd pollFd[MAX_EVENTS];
	vector<Channel*> channels;
	BSTree activeUsers;
	void *commandHandler;
	void executeCommand(vector<string> commands, int fd);
};


#endif
