#include "UnknownCommand.hpp"

string UnknownCommand::getName() const {
	return "UNKNOWN";
}

void UnknownCommand::execute(Server &server, string &command, int fd) {
	server.getPollFd(); //Doing this to disable unused parameter warning since this is a school project which means there are no exceptions to rules that need exceptions
	Template err = Template(ErrorMessages::ERR_UNKNOWN_COMMAND);
	Placeholder commandP = Placeholder("command", command);
	err.addPlaceholders(commandP);

	string reply = err.getString();
	send(fd, reply.c_str(), reply.length(), 0);
}
