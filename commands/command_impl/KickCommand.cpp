#include "KickCommand.hpp"
std::vector<std::string> splitString(const std::string& str, const std::string &split);
std::string joinString(std::vector<std::string> &split, const std::string &separator, int skip);

string KickCommand::getName() const {
	return "KICK";
}

void KickCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL || !user->isRegisterFinished()) {
		Template plt = Template(ErrorMessages::ERR_NOTREGISTERED);
		plt.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		string reply = plt.getString();
		send(fd, reply.c_str(), reply.length(), 0);
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
		Template replyT = Template(ErrorMessages::ERR_CHANOPRIVSNEEDED);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		replyT.addPlaceholders(Placeholder("channel", channel->getName()));
		std::string reply = replyT.getString();
		send(user->getFd(), reply.c_str(), reply.length(), 0);
		return;
	}

	User *kick = server.getUser(commandParts[1]);
	if (kick == NULL) {
		Template replyT = Template(ErrorMessages::ERR_USERNOTINCHANNEL);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		replyT.addPlaceholders(Placeholder("user", commandParts[1]));
		replyT.addPlaceholders(Placeholder("channel", channel->getName()));
		std::string reply = replyT.getString();
		send(user->getFd(), reply.c_str(), reply.length(), 0);
		return;
	}

	std::string reason;
	if (commandParts.size() > 2) {
		reason = joinString(commandParts, " ", 2);
	} else {
		reason = "Kicked by operator.";
	}
	Template replyT = Template(ReplyMessages::KICKMSG);
	replyT.addPlaceholders(Placeholder("nick", user->getNick()));
	replyT.addPlaceholders(Placeholder("affected", kick->getNick()));
	replyT.addPlaceholders(Placeholder("channel", channel->getName()));
	replyT.addPlaceholders(Placeholder("reason", reason));
	channel->broadcastMessage(replyT.getString());
	channel->removeUser(kick->getFd());
}
