#include "ModeCommand.hpp"
std::vector<std::string> splitString(const std::string& str, const std::string &split);

string ModeCommand::getName() const {
	return "MODE";
}
//received command: {MODE} with content {#example}
//possible response :server 324 <nick> <channel> +tn
//	+tn should be the mode
//Another possible command for this could be something with an extra argument for what the mode change should be like:
//	MODE target [+|-][mode] [parameter(s)]
void ModeCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL) {
		//TODO ERROR
		return;
	}

	std::vector<std::string> commandParts = splitString(command, " ");
	if (commandParts.size() == 1) {
		respondModeChannel(server, command, fd, user);
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
	if (commandParts[1] == "+o") {
		setOp(server, commandParts[0], user, commandParts[2], true);
	} else if (commandParts[1] == "-o") {
		setOp(server, commandParts[0], user, commandParts[2], false);
	}
	//TODO implement setting modes
}

void ModeCommand::respondModeChannel(Server &server, string &channelName, int fd, User *user) {
	Channel* channel = server.getChannel(channelName);
	if (channel == NULL) {
		Template replyT = Template(ErrorMessages::ERR_NOSUCHCHANNEL);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		replyT.addPlaceholders(Placeholder("channel", channelName));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}

	Template modeT = Template(ReplyMessages::RPL_CHANNELMODEIS);
	modeT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
	modeT.addPlaceholders(Placeholder("channel", channel->getName()));
	modeT.addPlaceholders(Placeholder("nick", "")); // Not affecting a specific user
	if (channel->isOp(user))
		modeT.addPlaceholders(Placeholder("mode", "+no")); // Have to be in the channel to send messages to it, user is OP
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
	if (actor->getUsername() != "Teriuihi") {
		//TODO permission error (only i can make ppl OP)
		//Yes this is not secure, its not meant to be, its just an example of how the OP command could work
		//	if this were to be for real id make it so you'd need an extra password to login as Teriuihi or
		//	make a custom command for getting OP with a specific command
		return;
	}
	User *user = server.getUser(affectedNick);
	if (user == NULL)
		return; //TODO error
	Template channelModeT = Template(ReplyMessages::RPL_CHANNELMODEIS);
	channelModeT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
	channelModeT.addPlaceholders(Placeholder("channel", channel->getName()));
	channelModeT.addPlaceholders(Placeholder("nick", user->getNick()));
	if (state) {
		channelModeT.addPlaceholders(Placeholder("mode", "+no")); //Channel is in n mode and user got OP
		channel->addOp(user);
		//TODO notify user with RPL_YOUREOPER
	} else {
		channelModeT.addPlaceholders(Placeholder("mode", "-o")); //User loses OP
		channel->removeOp(user);
	}
	channel->broadcastMessage(channelModeT.getString());
}
