#include "PartCommand.hpp"
std::vector<std::string> splitString(const std::string& str, const std::string &split);
std::string joinString(std::vector<std::string> &split, const std::string &separator, int skip);

string PartCommand::getName() const {
	return "PART";
}

void PartCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL || !user->isRegisterFinished()) {
		send(fd, ErrorMessages::ERR_NOTREGISTERED.c_str(), ErrorMessages::ERR_NOTREGISTERED.length(), 0);
		return;
	}
	std::vector<std::string> commandParts = splitString(command, " ");
	if (commandParts.empty()) {
		Template replyT = Template(ErrorMessages::ERR_NEEDMOREPARAMS);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		replyT.addPlaceholders(Placeholder("command", command));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	Channel* channel = server.getChannel(commandParts[0]);
	if (channel == NULL) {
		Template replyT = Template(ErrorMessages::ERR_NOSUCHCHANNEL);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		replyT.addPlaceholders(Placeholder("channel", commandParts[0]));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	if (channel->getUser(user->getFd()) == NULL) {
		Template replyT = Template(ErrorMessages::ERR_NOTONCHANNEL);
		replyT.addPlaceholders(Placeholder("hostname", user->getHostname()));
		replyT.addPlaceholders(Placeholder("channel", channel->getName()));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	Template replyT = Template(ReplyMessages::PARTMSG);
	replyT.addPlaceholders(Placeholder("nick", user->getNick()));
	replyT.addPlaceholders(Placeholder("channel", channel->getName()));
	replyT.addPlaceholders(Placeholder("reason", joinString(commandParts, " ", 1)));
	std::string reply = replyT.getString();
	channel->removeUser(fd);
	channel->sendMessage(user, reply);
}
