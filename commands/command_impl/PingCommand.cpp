#include "PingCommand.hpp"

string PingCommand::getName() const {
	return "PING";
}

void PingCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL || !user->isRegisterFinished()) {
		send(fd, ErrorMessages::ERR_NOTREGISTERED.c_str(), ErrorMessages::ERR_NOTREGISTERED.length(), 0);
		return;
	}
	string response = "PONG " + command;
	send(fd, response.c_str(), response.length(), 0);
}
