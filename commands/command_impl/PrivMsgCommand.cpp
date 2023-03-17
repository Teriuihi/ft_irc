#include "PrivMsgCommand.hpp"
std::vector<std::string> splitString(const std::string& str, const std::string &split);

string PrivMsgCommand::getName() const {
	return "PRIVMSG";
}

void PrivMsgCommand::sendNoRecipientMessage(Server &server, string &command, int fd) {
	Template plt = Template(ErrorMessages::ERR_NORECIPIENT);
	plt.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
	plt.addPlaceholders(Placeholder("command", command));
	string reply = plt.getString();
	send(fd, reply.c_str(), reply.length(), 0);
}

void PrivMsgCommand::sendNoTextToSendMessage(Server &server, int fd) {
	Template plt = Template(ErrorMessages::ERR_NOTEXTTOSEND);
	plt.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
	string reply = plt.getString();
	send(fd, reply.c_str(), reply.length(), 0);
}

void PrivMsgCommand::sendChannelMessage(Server &server, int fd, string const &target, Template &channelMessageT, User *user) {
	Channel *channel = server.getChannel(target);
	if (channel == NULL) {
		cout << "No channel with that name found" << endl;
		return;
		//TODO send err msg
	}
	if (channel->getUser(fd) == NULL) {
		//TODO error not in channel ?
		return;
	}
	channelMessageT.addPlaceholders(Placeholder("channel", channel->getName()));
	string modifiedMsg = channelMessageT.getString();
	channel->sendMessage(user, modifiedMsg);
}

void PrivMsgCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL || !user->isAuthed())
		return;
	vector<string> commandParts = splitString(command, " ");
	if (commandParts.empty() || *command.begin() == ':') {
		sendNoRecipientMessage(server, command, fd);
		return;
	} else if (commandParts.size() == 1) {
		sendNoTextToSendMessage(server, fd);
		return;
	}
	string target = commandParts[0];
	size_t pos = command.find(" :");
	if (pos == string::npos || command.length() < pos + 2) {
		sendNoTextToSendMessage(server, fd);
		return;
	}
	pos += 2;
	string textToSend = command.substr(pos, command.length() - pos);
	Placeholder nickP = Placeholder("nick", user->getNick());
	Placeholder userP = Placeholder("user", user->getUsername());
	Placeholder hostP = Placeholder("host", user->getHostname());
	Placeholder messageP = Placeholder("message", textToSend);

	Template channelMessageT = Template(ReplyMessages::PRIVMSG);
	channelMessageT.addPlaceholders(nickP);
	channelMessageT.addPlaceholders(userP);
	channelMessageT.addPlaceholders(hostP);
	channelMessageT.addPlaceholders(messageP);

	for (vector<string>::const_iterator it = commandParts.begin(); it != commandParts.end(); it++) {
		if (*it->begin() == ':')
			break;
		if (*it->begin() == '#') {
			sendChannelMessage(server, fd, *it, channelMessageT, user);
		} else {
			//TODO handle dm'ing user?
			//	Are we ignoring $?
		}
	}
}
