#include "UserCommand.hpp"
std::vector<std::string> splitString(const std::string& str, const std::string &split);

string UserCommand::getName() const {
	return "USER";
}
//const string RPL_WELCOME = ":irc.example.com 001 <nick> Welcome to the Internet Relay Network <nick>!<user>@<host>";
//const string RPL_YOURHOST = ":irc.example.com 001 <nick> Your host is <servername>, running version <ver>";
//const string RPL_CREATED = ":irc.example.com 001 <nick> This server was created 16/03/2023";
//const string RPL_MYINFO = ":irc.example.com 001 <nick> <servername> <version> <available user modes> <available channel modes>";

//received message is username status_bit_mask star? :real name
void UserCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL || !user->isAuthed())
		return;
	std::vector<std::string> commandParts = splitString(command, " ");
	if (commandParts.size() < 4) {
		std::cout << "Unexpected command length" << std::endl;
		return;
	}
	user->setUsername(commandParts[0]);
	size_t pos = command.find(commandParts[3]);
	if (pos != std::string::npos) {
		user->setRealName(command.substr(pos));
	} else {
		user->setRealName(commandParts[3]);
	}

	Template welcome = Template(ReplyMessages::RPL_WELCOME);
	Placeholder nickP = Placeholder("nick", user->getNick());
	Placeholder userP = Placeholder("user", user->getUsername());
	Placeholder hostP = Placeholder("host", "localhost"); //TODO fix
	welcome.addPlaceholders(nickP);
	welcome.addPlaceholders(userP);
	welcome.addPlaceholders(hostP);

	string welcomeString = welcome.getString();
	cout << "Replying to user command with: {" << welcomeString << "}" << endl;
	send(fd, welcomeString.c_str(), welcomeString.length(), 0);
}
