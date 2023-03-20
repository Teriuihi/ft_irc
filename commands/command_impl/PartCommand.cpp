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
	Template plt = Template(ReplyMessages::PARTMSG);
	plt.addPlaceholders(Placeholder("nick", user->getNick()));
	plt.addPlaceholders(Placeholder("username", user->getUsername()));
	plt.addPlaceholders(Placeholder("hostname", user->getHostname()));
	plt.addPlaceholders(Placeholder("channel", channel->getName()));
	plt.addPlaceholders(Placeholder("reason", joinString(commandParts, " ", 1)));
	std::string reply = plt.getString();
	channel->removeUser(fd);
	channel->sendMessage(user, reply);
}
