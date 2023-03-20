#include "PasswordCommand.hpp"

string PasswordCommand::getName() const {
	return "PASS";
}

void PasswordCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user != NULL) {
		Template replyT = Template(ErrorMessages::ERR_ALREADYREGISTRED);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	if (command == server.getPassword())
		server.addUser(fd, new User(fd));
	else {
		Template replyT = Template(ErrorMessages::ERR_PASSWDMISMATCH);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
	}
}
