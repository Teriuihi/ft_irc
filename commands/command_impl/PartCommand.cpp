#include "PartCommand.hpp"
std::vector<std::string> splitString(const std::string& str, const std::string &split);

string PartCommand::getName() const {
	return "PART";
}

void PartCommand::execute(Server &server, string &command, int fd) {
	string notconst = ":<nick>!<username>@<hostname> PART <channel> <reason>\n";
	User *user = server.getUser(fd);
	if (user == NULL || !user->isAuthed()) {
		//TODO ERROR
		return;
	}
	std::vector<std::string> commandParts = splitString(command, " ");
	if (commandParts.size() < 2) {
		//TODO error
		return;
	}
	Channel* channel = server.getChannel(commandParts[0]);
	if (channel == NULL)
		return; //TODO error?
	Template plt = Template(notconst);
	plt.addPlaceholders(Placeholder("nick", user->getNick()));
	plt.addPlaceholders(Placeholder("username", user->getUsername()));
	plt.addPlaceholders(Placeholder("hostname", user->getHostname()));
	plt.addPlaceholders(Placeholder("channel", channel->getName()));
	plt.addPlaceholders(Placeholder("reason", command));
	std::string reply = plt.getString();
	channel->removeUser(fd);
	channel->sendMessage(user, reply);
}
