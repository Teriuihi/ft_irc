#include "QuitCommand.hpp"

string QuitCommand::getName() const {
	return "QUIT";
}

void QuitCommand::execute(Server &server, string &command, int fd) {
	server.disconnect(fd, command);
}
