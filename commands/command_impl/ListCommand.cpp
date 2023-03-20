#include "ListCommand.hpp"

string ListCommand::getName() const {
	return "LIST";
}

void ListCommand::execute(Server &server, string &command, int fd) {\
	User *user = server.getUser(fd);
	if (user == NULL) {
		send(fd, ErrorMessages::ERR_NOTREGISTERED.c_str(), ErrorMessages::ERR_NOTREGISTERED.length(), 0);
		return;
	}

	vector<Channel*> channels = server.getChannels();
	Template listT = Template(ReplyMessages::RPL_LIST);
	listT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
	listT.addPlaceholders(Placeholder("nick", user->getNick()));

	for (vector<Channel*>::const_iterator it = channels.begin(); it != channels.end(); it++) {
		listT.addPlaceholders(Placeholder("channel", (*it)->getName()));
		listT.addPlaceholders(Placeholder("users", (*it)->getUserCount()));
		listT.addPlaceholders(Placeholder("topic", (*it)->getTopic()));
		string listM = listT.getString();
		send(fd, listM.c_str(), listM.size(), 0);
	}

	Template listEndT = Template(ReplyMessages::RPL_LISTEND);
	listEndT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
	listEndT.addPlaceholders(Placeholder("nick", user->getNick()));
	string listEndM = listEndT.getString();
	send(fd, listEndM.c_str(), listEndM.size(), 0);
	command.size(); //This param is unused but that's not allowed by the subject but it needs to be
}
