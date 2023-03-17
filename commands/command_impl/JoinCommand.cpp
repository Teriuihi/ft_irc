#include "JoinCommand.hpp"

string JoinCommand::getName() const {
	return "JOIN";
}

void JoinCommand::execute(Server &server, string &command, int fd) { //TODO handle joining multiple channels in one command
	string notconst = "<nick>!<username>@<hostname> JOIN <channel>\n"; //TODO move to constants
	string notconst2 = ":<nick>!<username>@<hostname> JOIN <channel>\n";
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
	Placeholder hostnameP = Placeholder("hostname", "localhost"); //TODO localhost might need to change
	Template plt = Template(notconst);
	Template plt2 = Template(notconst2);
	plt.addPlaceholders(nickP);
	plt.addPlaceholders(usernameP);
	plt.addPlaceholders(channelP);
	plt.addPlaceholders(hostnameP);
	plt2.addPlaceholders(nickP);
	plt2.addPlaceholders(usernameP);
	plt2.addPlaceholders(channelP);
	plt2.addPlaceholders(hostnameP);
	string reply = plt.getString();
	send(fd, reply.c_str(), reply.length(), 0);
	channel->sendMessage(user, plt2.getString());
}
