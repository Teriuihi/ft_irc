#include "UserCommand.hpp"

std::vector<std::string> splitString(const std::string &str, const std::string &split);

string UserCommand::getName() const {
	return "USER";
}

void UserCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL) {
		Template plt = Template(ErrorMessages::ERR_NOTREGISTERED);
		plt.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		string reply = plt.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	if (user->isRegisterFinished()) {
		Template replyT = Template(ErrorMessages::ERR_ALREADYREGISTERED);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	std::vector<std::string> commandParts = splitString(command, " ");
	if (commandParts.size() < 4) {
		Template replyT = Template(ErrorMessages::ERR_NEEDMOREPARAMS);
		replyT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
		replyT.addPlaceholders(Placeholder("nick", user->getNick()));
		replyT.addPlaceholders(Placeholder("command", command));
		std::string reply = replyT.getString();
		send(fd, reply.c_str(), reply.length(), 0);
		return;
	}
	user->setUsername(commandParts[0]);
	user->setHostname(commandParts[1]);
	user->setServername(commandParts[2]);
	size_t pos = command.find(commandParts[3]);
	if (pos != std::string::npos) {
		user->setRealName(command.substr(pos + 1));
	} else {
		user->setRealName(commandParts[3]);
	}
	user->setRegisterFinished(true);

	Placeholder serverHostP = Placeholder("server_hostname", server.getHostname());
	Placeholder nickP = Placeholder("nick", user->getNick());
	Placeholder userP = Placeholder("user", user->getUsername());
	Placeholder hostP = Placeholder("host", user->getHostname());
	Placeholder verP = Placeholder("ver", "1.0");
	Placeholder versionP = Placeholder("version", "1.0");
	Placeholder serverNameP = Placeholder("servername", server.getName());
	Placeholder userModesP = Placeholder("available user modes", "o");
	Placeholder channelModesP = Placeholder("available channel modes", "");

	Template welcomeT = Template(ReplyMessages::RPL_WELCOME);
	welcomeT.addPlaceholders(serverHostP);
	welcomeT.addPlaceholders(nickP);
	welcomeT.addPlaceholders(userP);
	welcomeT.addPlaceholders(hostP);
	string welcomeR = welcomeT.getString();
	send(fd, welcomeR.c_str(), welcomeR.length(), 0);

	Template yourHostT = Template(ReplyMessages::RPL_YOURHOST);
	yourHostT.addPlaceholders(serverHostP);
	yourHostT.addPlaceholders(serverNameP);
	yourHostT.addPlaceholders(nickP);
	yourHostT.addPlaceholders(verP);
	string yourHostR = yourHostT.getString();
	send(fd, yourHostR.c_str(), yourHostR.length(), 0);

	Template createdT = Template(ReplyMessages::RPL_CREATED);
	createdT.addPlaceholders(serverHostP);
	createdT.addPlaceholders(nickP);
	string createdR = createdT.getString();
	send(fd, createdR.c_str(), createdR.length(), 0);

	//const std::string RPL_MYINFO = ":<server_hostname> 004 <nick> :<servername> <version> <available user modes> <available channel modes>\n";
	Template myInfoT = Template(ReplyMessages::RPL_MYINFO);
	myInfoT.addPlaceholders(serverHostP);
	myInfoT.addPlaceholders(nickP);
	myInfoT.addPlaceholders(serverNameP);
	myInfoT.addPlaceholders(versionP);
	myInfoT.addPlaceholders(userModesP);
	myInfoT.addPlaceholders(channelModesP);
	string myInfoR = myInfoT.getString();
	send(fd, myInfoR.c_str(), myInfoR.length(), 0);
}
