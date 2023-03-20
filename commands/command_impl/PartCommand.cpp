#include "PartCommand.hpp"
std::vector<std::string> splitString(const std::string& str, const std::string &split);

string PartCommand::getName() const {
	return "PART";
}

void PartCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL) {
		//TODO ERROR
		return;
	}
	std::vector<std::string> commandParts = splitString(command, " ");
	if (commandParts.size() < 2) {
		Template replyT = Template(ErrorMessages::ERR_NEEDMOREPARAMS);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("command", command));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	Channel* channel = server.getChannel(commandParts[0]);
	if (channel == NULL) {
		Template replyT = Template(ErrorMessages::ERR_NOSUCHCHANNEL);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("channel", commandParts[0]));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	Template plt = Template(ReplyMessages::PARTMSG);
	plt.addPlaceholders(Placeholder("nick", user->getNick()));
	plt.addPlaceholders(Placeholder("username", user->getUsername()));
	plt.addPlaceholders(Placeholder("hostname", user->getHostname()));
	plt.addPlaceholders(Placeholder("channel", channel->getName()));
	plt.addPlaceholders(Placeholder("reason", command));
	std::string reply = plt.getString();
	channel->removeUser(fd);
	channel->sendMessage(user, reply);
}
