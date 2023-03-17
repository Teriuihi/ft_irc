#include "JoinCommand.hpp"

string JoinCommand::getName() const {
	return "JOIN";
}

void JoinCommand::execute(Server &server, string &command, int fd) { //TODO handle joining multiple channels in one command
	User *user = server.getUser(fd);
	if (user == NULL || !user->isAuthed()) {
		//TODO ERROR
		return;
	}
	Channel *channel = server.getChannel(command);
	if (channel == NULL) {
		Template plt = Template(ErrorMessages::ERR_BADCHANNELKEY);
		Placeholder channelP = Placeholder("channel", command);
		plt.addPlaceholders(channelP);
		string reply = plt.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	channel->addUser(user->getFd(), user);

	Placeholder nickP = Placeholder("nick", user->getNick());
	Placeholder usernameP = Placeholder("username", user->getUsername());
	Placeholder channelP = Placeholder("channel", channel->getName());
	Placeholder hostnameP = Placeholder("hostname", user->getHostname());
	Placeholder topicP = Placeholder("topic", channel->getTopic());
	Placeholder userListP = Placeholder("user_list", channel->getUserList());

	Template joinT = Template(ReplyMessages::JOIN);
	joinT.addPlaceholders(nickP);
	joinT.addPlaceholders(usernameP);
	joinT.addPlaceholders(channelP);
	joinT.addPlaceholders(hostnameP);
	channel->sendMessage(user, joinT.getString());

	Template topicT = Template(ReplyMessages::RPL_TOPIC);
	topicT.addPlaceholders(channelP);
	topicT.addPlaceholders(topicP);
	string topicReply = topicT.getString();
	send(fd, topicReply.c_str(), topicReply.length(), 0);

	Template nameT = Template(ReplyMessages::RPL_NAMREPLY);
	nameT.addPlaceholders(channelP);
	nameT.addPlaceholders(userListP);
	string userListReply = nameT.getString();
	send(fd, userListReply.c_str(), userListReply.length(), 0);

	Template nameEndT = Template(ReplyMessages::RPL_ENDOFNAMES);
	nameEndT.addPlaceholders(channelP);
	string userListEndReply = nameEndT.getString();
	send(fd, userListEndReply.c_str(), userListEndReply.length(), 0);
}
