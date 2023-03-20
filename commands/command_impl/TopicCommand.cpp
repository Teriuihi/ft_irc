#include "TopicCommand.hpp"
std::vector<std::string> splitString(const std::string& str, const std::string &split);
std::string joinString(std::vector<std::string> &split, const std::string &separator, int skip);

string TopicCommand::getName() const {
	return "TOPIC";
}

void TopicCommand::execute(Server &server, string &command, int fd) {
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

	if (commandParts.size() == 1) {
		Template replyT = Template(ReplyMessages::RPL_TOPIC);
		if (channel->getTopic().empty()) {
			replyT = Template(ReplyMessages::RPL_NOTOPIC);
		} else {
			replyT.addPlaceholders(Placeholder("topic", channel->getTopic()));
		}
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		replyT.addPlaceholders(Placeholder("channel", channel->getName()));
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
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

	string topic = joinString(commandParts, " ", 1);
	topic = topic.substr(1, topic.length());
	channel->setTopic(topic);
	Template replyT = Template(ReplyMessages::RPL_TOPIC);
	replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
	replyT.addPlaceholders(Placeholder("nick", user->getNick()));
	replyT.addPlaceholders(Placeholder("channel", channel->getName()));
	replyT.addPlaceholders(Placeholder("topic", channel->getTopic()));
	channel->broadcastMessage(replyT.getString());
}
