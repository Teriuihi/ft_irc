#include "JoinCommand.hpp"

string JoinCommand::getName() const {
	return "JOIN";
}
//TODO handle joining multiple channels in one command
//TODO sometimes joining doesn't notify the other client properly?
void JoinCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL) {
		send(fd, ErrorMessages::ERR_NOTREGISTERED.c_str(), ErrorMessages::ERR_NOTREGISTERED.length(), 0);
		return;
	}
	Channel *channel = server.getChannel(command);
	if (channel == NULL) {
		Template plt = Template(ErrorMessages::ERR_BADCHANNELKEY);
		plt.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		plt.addPlaceholders(Placeholder("nick", user->getNick()));
		plt.addPlaceholders(Placeholder("channel", command));
		string reply = plt.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	channel->addUser(user->getFd(), user);

	Placeholder serverHostP = Placeholder("server_hostname", server.getHostname());
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
	string joinR = joinT.getString();
	channel->sendMessage(user, joinT.getString());
	send(fd, joinR.c_str(), joinR.length(), 0);

	Template topicT = Template(ReplyMessages::RPL_TOPIC);
	topicT.addPlaceholders(serverHostP);
	topicT.addPlaceholders(nickP);
	topicT.addPlaceholders(channelP);
	topicT.addPlaceholders(topicP);
	string topicReply = topicT.getString();
	send(fd, topicReply.c_str(), topicReply.length(), 0);

	Template nameT = Template(ReplyMessages::RPL_NAMREPLY);
	nameT.addPlaceholders(serverHostP);
	nameT.addPlaceholders(nickP);
	nameT.addPlaceholders(channelP);
	nameT.addPlaceholders(userListP);
	string userListReply = nameT.getString();
	send(fd, userListReply.c_str(), userListReply.length(), 0);

	Template nameEndT = Template(ReplyMessages::RPL_ENDOFNAMES);
	nameEndT.addPlaceholders(serverHostP);
	nameEndT.addPlaceholders(nickP);
	nameEndT.addPlaceholders(channelP);
	string userListEndReply = nameEndT.getString();
	send(fd, userListEndReply.c_str(), userListEndReply.length(), 0);
}
