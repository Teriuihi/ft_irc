#include "PingCommand.hpp"

string PingCommand::getName() const {
	return "PING";
}

void PingCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL || !user->isRegisterFinished()) {
		Template plt = Template(ErrorMessages::ERR_NOTREGISTERED);
		plt.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		string reply = plt.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	string response = "PONG " + command;
	send(fd, response.c_str(), response.length(), 0);
}
