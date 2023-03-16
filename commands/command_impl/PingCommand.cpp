#include "PingCommand.hpp"

string PingCommand::getName() const {
	return "PING";
}

void PingCommand::execute(Server &server, string &command, int fd) {
	if (server.getUser(fd) == NULL)
		return;
	string response = "PONG " + command;
	send(fd, response.c_str(), response.length(), 0);
}
