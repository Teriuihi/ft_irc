#include "PingCommand.hpp"

string PingCommand::getName() const {
	return "PING";
}

void PingCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL || !user->isAuthed())
		return;
	string response = "PONG " + command;
	send(fd, response.c_str(), response.length(), 0);
}
