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
	void addUser(int fd, User *user) { activeUsers.insert(fd, user); }
	User* getUser(int fd) {
		Node<User> *node = activeUsers.getNode(fd);
		if (node == NULL)
			return NULL;
		return node->getValue();
	}

	User* getUser(const string& searchNick) {
		vector<User*> users = activeUsers.getAll();
		for (vector<User*>::const_iterator it = users.begin(); it != users.end(); ++it) {
			if ((*it)->getNick() == searchNick)
				return *it;
		}
		return NULL;
	}

	const vector<Channel *> &getChannels() const;

	std::string getPassword() { return password; }
	void forwardMessage(char *message);
	void receivedMessage(char *message, int fd);
	void closeServer() const;
	Channel* getChannel(const string& name);
	vector<Channel *> getAllChannelsForUser(int fd);
	const string &getName() const;
	const string &getHostname() const;
	void disconnect(int fd, const string& reason);
	int *getClientSockets();

private:
	int sockFd;
	std::string password;
	struct sockaddr_in serv_addr;
	struct pollfd pollFd[MAX_EVENTS];
	vector<Channel*> channels;
	BSTree<User> activeUsers;
	map<int, std::string> incompleteText;
	std::string hostname;
	std::string name;
	int clientSockets[MAX_CLIENTS];
	void *commandHandler;
	void executeCommand(vector<string> commands, int fd);
	void removeUser(int fd) { activeUsers.remove(fd); }
};


#endif
