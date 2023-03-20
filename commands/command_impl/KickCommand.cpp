#include "KickCommand.hpp"
std::vector<std::string> splitString(const std::string& str, const std::string &split);

string KickCommand::getName() const {
	return "KICK";
}

void KickCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL) {
		//TODO ERR_NOTONCHANNEL
		return;
	}

	std::vector<std::string> commandParts = splitString(command, " ");
	if (commandParts.size() < 2) {
		Template replyT = Template(ErrorMessages::ERR_NEEDMOREPARAMS);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		replyT.addPlaceholders(Placeholder("command", command));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}

	Channel *channel = server.getChannel(commandParts[0]);
	if (channel == NULL) {
		Template replyT = Template(ErrorMessages::ERR_NOSUCHCHANNEL);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		replyT.addPlaceholders(Placeholder("channel", commandParts[0]));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}

	if (!channel->isOp(user)) {
		//TODO ERR_CHANOPRIVSNEEDED
		return;
	}

	User *kick = server.getUser(commandParts[1]);
	if (kick == NULL) {
		//TODO ERR_USERNOTINCHANNEL
		return;
	}

	channel->removeUser(kick->getFd());
	if (commandParts.size() > 2) {
		//TODO notify with reason
	} else {
		//TODO notify with default reason;
	}
}
