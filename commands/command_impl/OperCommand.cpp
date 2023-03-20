#include "OperCommand.hpp"
std::vector<std::string> splitString(const std::string& str, const std::string &split);

string OperCommand::getName() const {
	return "OPER";
}

void OperCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL || !user->isRegisterFinished()) {
		send(fd, ErrorMessages::ERR_NOTREGISTERED.c_str(), ErrorMessages::ERR_NOTREGISTERED.length(), 0);
		return;
	}

	std::vector<std::string> commandParts = splitString(command, " ");
	if (commandParts.size() != 2) {
		Template replyT = Template(ErrorMessages::ERR_NEEDMOREPARAMS);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		replyT.addPlaceholders(Placeholder("command", command));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}

	User *affected = server.getUser(commandParts[0]);
	if (affected == NULL) {
		Template replyT = Template(ErrorMessages::ERR_NOSUCHNICK);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		replyT.addPlaceholders(Placeholder("channel", ""));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}

	if (commandParts[1] != OPER_PASS) {
		Template replyT = Template(ErrorMessages::ERR_PASSWDMISMATCH);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}

	affected->setServerOp(true);
	Template replyT = Template(ReplyMessages::RPL_YOUREOPER);
	replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
	replyT.addPlaceholders(Placeholder("nick", affected->getNick()));
	std::string reply = replyT.getString();
	send(affected->getFd(), reply.c_str(), reply.length(), 0);
}
