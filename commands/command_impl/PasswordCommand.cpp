#include "PasswordCommand.hpp"

string PasswordCommand::getName() const {
	return "PASSWORD";
}

void PasswordCommand::execute(Server &server, string &command, int fd) {
	if (command == server.getPassword())
		server.addUser(fd, new User(fd, true));
	else {
		server.addUser(fd, new User(fd, false));
		std::string reply = ErrorMessages::ERR_PASSWDMISMATCH;
		send(fd, reply.c_str(), reply.length(), 0);
	}
}
