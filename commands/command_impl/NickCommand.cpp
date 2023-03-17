#include "NickCommand.hpp"

string NickCommand::getName() const {
	return "NICK";
}

void NickCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL || !user->isAuthed())
		return; //TODO error?
	if (command.empty())
		return; //TODO error?
	//TODO check nick len?
	user->setNick(command);
}
