#include "PasswordCommand.hpp"

string PasswordCommand::getName() const {
	return "PASSWORD";
}

void PasswordCommand::execute(Server &server, string &command, int fd) {
	if (command == server.getPassword())
		server.addUser(fd, new User(fd, true));
	else {
		server.addUser(fd, new User(fd, false));
		Template replyT = Template(ErrorMessages::ERR_PASSWDMISMATCH);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
	}
}
