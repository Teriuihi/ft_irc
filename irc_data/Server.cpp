#include <cstring>
#include <sys/poll.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include "../helper_files/badFixHeader.hpp"

Server::Server(int port, const std::string &password) : serv_addr(), pollFd() {
	this->password = password;
	this->commandHandler = new CommandHandler();
	sockFd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockFd < 0) {
		throw runtime_error("Error creating socket");
	}

	int opt = 1;
	if (setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
		throw runtime_error("Error setting socket options");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	if (bind(sockFd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		throw runtime_error("Error binding socket to address");
	}

	if (listen(sockFd, MAX_CLIENTS) < 0) {
		throw runtime_error("Error listening for connections");
	}

	cout << "Server is listening on port " << port << endl;

	fcntl(sockFd, F_SETFL, O_NONBLOCK);

	pollFd[0].fd = sockFd;
	pollFd[0].events = POLLIN | POLLOUT | POLLHUP | POLLERR;
	for (int i = 1; i <= MAX_CLIENTS; i++) {
		pollFd[i].fd = -1;
	}

	channels.push_back(new Channel("#example"));
}

void Server::closeServer() const { //TODO do this in de-constructor?
	for (int i = 1; i <= MAX_CLIENTS; i++) {
		if (pollFd[i].fd != -1) {
			close(pollFd[i].fd);
		}
	}

	for (vector<Channel*>::const_iterator it = channels.begin(); it != channels.end(); ++it) {
		delete *it;
	}

	close(sockFd);
}

Channel *Server::getChannel(const string& name) {
	for (vector<Channel*>::const_iterator it = channels.begin(); it != channels.end(); ++it) {
		if ((*it)->getName() == name) {
			return *it;
		}
	}
	throw out_of_range("No channel with that name in this vector");
}

void Server::forwardMessage(char *message) {
	cout << "received message" << message << endl;
	for (int i = 1; i <= MAX_CLIENTS; i++) {
		send(pollFd[i].fd, message, strlen(message), 0);
	}
}

void Server::executeCommand(std::vector<std::string> commands, int fd) {
	for (std::vector<std::string>::size_type i = 0; i < commands.size(); i++) {
		string fullCommand = commands[i];
		if (*--fullCommand.end() == '\r')
			fullCommand = fullCommand.substr(0, fullCommand.length() - 1);
		size_t pos = fullCommand.find(' ');
		if (pos == std::string::npos) {
			return;
		}
		std::string name = fullCommand.substr(0, pos);
		if (fullCommand.length() < pos + 2) {
			cout << "received message seems too short, no command context, message was: {" << fullCommand << "}" << endl;
			return;
		}
		std::string command = fullCommand.substr(pos + 1);
		cout << "received command: {" << name << "} with content {" << command << "}" << endl;
		((CommandHandler*) commandHandler)->execute(name, *this, command, fd);
	}
}

std::vector<std::string> splitString(const std::string& str, const std::string &split);

void Server::receivedMessage(char *message, int fd) {
	string msg(message);
	if (*--msg.end() != '\n') {
		cout << "Received incomplete message" << endl;
	}
	msg = msg.substr(0, msg.length() - 1);
	size_t pos = msg.find(']');
	if (pos != std::string::npos && pos + 2 >= msg.length()) {
		cout << "Received message seems too short, message was: {" << msg << "}" << endl;
		return;
	}
	pos += 2;
	string fullCommand = msg.substr(pos, msg.length());
	std::vector<std::string> commands = splitString(fullCommand, "\n");
	executeCommand(commands, fd);
//	string reply = "";
//	if (fullCommand.find("USER ") == 0) {
//		reply = ":irc.example.com 001 Teri :Welcome to the ft_irc server Teri!\n";
//		//TODO set user
//	} else if (fullCommand.find("JOIN ") == 0) {
//		reply = replyJoin(*this, message, user);
//	} else if (fullCommand.find("PING ") == 0) {
//		reply = "PONG" + fullCommand.substr(4);
//	}
//
//	if (reply.length() > 0)
//		send(fd, reply.c_str(), reply.length(), 0);
}