#include "UnknownCommand.hpp"

string UnknownCommand::getName() const {
	return "UNKNOWN";
}

void UnknownCommand::execute(Server &server, string &command, int fd) {
	server.getPollFd(); //Doing this to disable unused parameter warning since this is a school project which means there are no exceptions to rules that need exceptions
	send(fd, command.c_str(), command.length(), 0);
}
