#include "UserCommand.hpp"
std::vector<std::string> splitString(const std::string& str, const std::string &split);

string UserCommand::getName() const {
	return "USER";
}
//const std::string RPL_WELCOME = ":<server_hostname> 001 <nick> :Welcome to the Internet Relay Network <nick>!<user>@<host>\n";
//const std::string RPL_YOURHOST = ":<server_hostname> 002 <nick> :Your host is <servername>, running version <ver>\n";
//const std::string RPL_CREATED = ":<server_hostname> 003 <nick> :This server was created 16/03/2023\n";
//const std::string RPL_MYINFO = ":<server_hostname> 004 <nick> :<servername> <version> <available user modes> <available channel modes>\n";

//received message is username hostname servername :real name
void UserCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL)
		return;
	std::vector<std::string> commandParts = splitString(command, " ");
	if (commandParts.size() < 4) {
		std::cout << "Unexpected command length" << std::endl;
		return;
	}
	user->setUsername(commandParts[0]);
	user->setHostname(commandParts[1]);
	user->setServername(commandParts[2]);
	size_t pos = command.find(commandParts[3]);
	if (pos != std::string::npos) {
		user->setRealName(command.substr(pos));
	} else {
		user->setRealName(commandParts[3]);
	}

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
