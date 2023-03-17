#include "QuitCommand.hpp"

string QuitCommand::getName() const {
	return "QUIT";
}

void QuitCommand::execute(Server &server, string &command, int fd) {
	string notconst = ":<nick>!<username>@<hostname> QUIT <reason>\n";
	User *user = server.getUser(fd);
	if (user == NULL || !user->isAuthed()) {
		//TODO ERROR
		return;
	}
	std::vector<Channel*> channels = server.getAllChannelsForUser(fd);
	if (channels.empty())
		return;
	Template plt = Template(notconst);
	plt.addPlaceholders(Placeholder("nick", user->getNick()));
	plt.addPlaceholders(Placeholder("username", user->getUsername()));
	plt.addPlaceholders(Placeholder("hostname", user->getHostname()));
	plt.addPlaceholders(Placeholder("reason", command));
	std::string reply = plt.getString();
	for (vector<Channel*>::const_iterator it = channels.begin(); it != channels.end(); it++) {
		(*it)->removeUser(fd);
		(*it)->sendMessage(user, reply);
	}
	server.removeUser(fd);
}
