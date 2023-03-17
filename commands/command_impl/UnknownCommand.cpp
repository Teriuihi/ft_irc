#include "UnknownCommand.hpp"

string UnknownCommand::getName() const {
	return "UNKNOWN";
}

void UnknownCommand::execute(Server &server, string &command, int fd) {
	Template err = Template(ErrorMessages::ERR_UNKNOWN_COMMAND);
	err.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
	err.addPlaceholders( Placeholder("command", command));

	string reply = err.getString();
	send(fd, reply.c_str(), reply.length(), 0);
}
