#include "ModeCommand.hpp"
std::vector<std::string> splitString(const std::string& str, const std::string &split);

string ModeCommand::getName() const {
	return "MODE";
}

void ModeCommand::execute(Server &server, string &command, int fd) {
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
	if (commandParts.size() <= 2) {
		string tmp;
		respondModeChannel(server, commandParts[0], commandParts.size() == 2 ? commandParts[1] : tmp, fd, user);
		return;
	}
	if (commandParts.size() != 3) {
		Template replyT = Template(ErrorMessages::ERR_NEEDMOREPARAMS);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		replyT.addPlaceholders(Placeholder("command", command));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	if (commandParts[2] == "+o") {
		setOp(server, commandParts[0], user, commandParts[1], true);
	} else if (commandParts[2] == "-o") {
		setOp(server, commandParts[0], user, commandParts[1], false);
	}
}

void ModeCommand::respondModeChannel(Server &server, string &channelName, string &userName, int fd, User *actor) {
	Channel* channel = server.getChannel(channelName);
	if (channel == NULL) {
		Template replyT = Template(ErrorMessages::ERR_NOSUCHCHANNEL);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", actor->getNick()));
		replyT.addPlaceholders(Placeholder("channel", channelName));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}

	User *user = server.getUser(userName);
	if (!userName.empty() && user == NULL) {
		Template replyT = Template(ErrorMessages::ERR_NOSUCHNICK);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", actor->getNick()));
		replyT.addPlaceholders(Placeholder("channel", channelName));
		std::string reply = replyT.getString();
		send(actor->getFd(), reply.c_str(), reply.length(), 0);
		return;
	} else if (!userName.empty() && user != actor) {
		Template replyT = Template(ErrorMessages::ERR_USERSDONTMATCH);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", actor->getNick()));
		replyT.addPlaceholders(Placeholder("channel", channelName));
		std::string reply = replyT.getString();
		send(actor->getFd(), reply.c_str(), reply.length(), 0);
		return;
	}

	Template modeT = Template(ReplyMessages::RPL_CHANNELMODEIS);
	modeT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
	modeT.addPlaceholders(Placeholder("channel", channel->getName()));
	modeT.addPlaceholders(Placeholder("nick", "")); // Not affecting a specific actor
	if (user != NULL && channel->isOp(actor))
		modeT.addPlaceholders(Placeholder("mode", "+no")); // Have to be in the channel to send messages to it, actor is OP
	else
		modeT.addPlaceholders(Placeholder("mode", "+n")); // Have to be in the channel to send messages to it

	string modeS = modeT.getString();
	send(fd, modeS.c_str(), modeS.size(), 0);
}

void ModeCommand::setOp(Server &server, string &channelName, User *actor, string &affectedNick, bool state) {
	Channel *channel = server.getChannel(channelName);
	if (channel == NULL) {
		Template replyT = Template(ErrorMessages::ERR_NOSUCHCHANNEL);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", actor->getNick()));
		replyT.addPlaceholders(Placeholder("channel", channelName));
		std::string reply = replyT.getString();
		send(actor->getFd(), reply.c_str(), reply.length(), 0);
		return;
	}
	if (!actor->isServerOp() && !channel->isOp(actor)) {
		Template replyT = Template(ErrorMessages::ERR_CHANOPRIVSNEEDED);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", actor->getNick()));
		replyT.addPlaceholders(Placeholder("channel", channelName));
		std::string reply = replyT.getString();
		send(actor->getFd(), reply.c_str(), reply.length(), 0);
		return;
	}
	User *user = server.getUser(affectedNick);
	if (user == NULL) {
		Template replyT = Template(ErrorMessages::ERR_NOSUCHNICK);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", actor->getNick()));
		replyT.addPlaceholders(Placeholder("channel", channelName));
		std::string reply = replyT.getString();
		send(actor->getFd(), reply.c_str(), reply.length(), 0);
		return;
	} else if (user != actor) {
		Template replyT = Template(ErrorMessages::ERR_USERSDONTMATCH);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", actor->getNick()));
		replyT.addPlaceholders(Placeholder("channel", channelName));
		std::string reply = replyT.getString();
		send(actor->getFd(), reply.c_str(), reply.length(), 0);
		return;
	}
	Template channelModeT = Template(ReplyMessages::RPL_CHANNELMODEIS);
	channelModeT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
	channelModeT.addPlaceholders(Placeholder("channel", channel->getName()));
	channelModeT.addPlaceholders(Placeholder("nick", user->getNick()));
	if (state) {
		channelModeT.addPlaceholders(Placeholder("mode", "+no")); //Channel is in n mode and user got OP
		channel->addOp(user);
		Template replyT = Template(ReplyMessages::RPL_YOUREOPER);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		std::string reply = replyT.getString();
		send(user->getFd(), reply.c_str(), reply.length(), 0);
	} else {
		channelModeT.addPlaceholders(Placeholder("mode", "-o")); //User loses OP
		channel->removeOp(user);
	}
	channel->broadcastMessage(channelModeT.getString());
}
