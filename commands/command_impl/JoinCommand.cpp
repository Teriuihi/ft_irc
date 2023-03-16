#include "JoinCommand.hpp"

string JoinCommand::getName() const {
	return "JOIN";
}

void JoinCommand::execute(Server &server, string &command, int fd) {
	string notconst = "<nick>!something@localhost JOIN <channel>\n"; //TODO move to constants
	Channel *channel;
	try {
		channel = server.getChannel(command);
	} catch (std::exception &e) {
		cout << e.what() << endl;
		return;
	}
	User *user = server.getUser(fd);
	if (user == NULL) {
		//TODO ERROR
		return;
	}
	Placeholder nickPlaceholder = Placeholder("nick", user->getNick());
	Placeholder channelPlaceholder = Placeholder("channel", channel->getName());
	Template plt = Template(notconst);
	plt.addPlaceholders(nickPlaceholder);
	plt.addPlaceholders(channelPlaceholder);
	string reply = plt.getString();
	send(fd, reply.c_str(), reply.length(), 0);
}
