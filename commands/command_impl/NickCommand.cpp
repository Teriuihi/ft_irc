#include "NickCommand.hpp"
#include <cctype>
#include <clocale>

string NickCommand::getName() const {
	return "NICK";
}

bool isValidNick(std::string &nick) {
	if (nick.length() > 16 || nick.length() < 3)
		return false;
	std::string::iterator it = nick.begin();
	for (; it != nick.end(); it++) {
		if (!isalpha(*it))
			return false;
	}
	return true;
}

void NickCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL) {
		send(fd, ErrorMessages::ERR_NOTREGISTERED.c_str(), ErrorMessages::ERR_NOTREGISTERED.length(), 0);
		return;
	}
	if (server.getUser(command) != NULL) {
		Template replyT = Template(ErrorMessages::ERR_NICKNAMEINUSE);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", command));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
	}
	if (command.empty()) {
		Template replyT = Template(ErrorMessages::ERR_NEEDMOREPARAMS);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", command));
		replyT.addPlaceholders(Placeholder("command", command));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	if (isValidNick(command)) {
		user->setNick(command);
		return;
	}
	Template replyT = Template(ErrorMessages::ERR_ERRONEUSNICKNAME);
	replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
	replyT.addPlaceholders(Placeholder("nick", command));
	std::string reply = replyT.getString();
	send(fd, reply.c_str(), reply.length(), 0);
}
