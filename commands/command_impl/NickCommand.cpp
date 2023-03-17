#include "NickCommand.hpp"

string NickCommand::getName() const {
	return "NICK";
}

void NickCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL || !user->isAuthed())
		return;
	user->setNick(command);
}
