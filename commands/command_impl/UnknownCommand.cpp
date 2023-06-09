#include "UnknownCommand.hpp"

string UnknownCommand::getName() const {
	return "UNKNOWN";
}

void UnknownCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL || !user->isRegisterFinished()) {
		Template plt = Template(ErrorMessages::ERR_NOTREGISTERED);
		plt.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		string reply = plt.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	Template err = Template(ErrorMessages::ERR_UNKNOWN_COMMAND);
	err.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
	err.addPlaceholders(Placeholder("nick", user->getNick()));
	err.addPlaceholders(Placeholder("command", command));

	string reply = err.getString();
	send(fd, reply.c_str(), reply.length(), 0);
}
