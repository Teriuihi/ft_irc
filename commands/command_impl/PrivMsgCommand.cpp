#include "PrivMsgCommand.hpp"
std::vector<std::string> splitString(const std::string& str, const std::string &split);

string PrivMsgCommand::getName() const {
	return "PRIVMSG";
}

void PrivMsgCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL || !user->isAuthed())
		return;
	std::vector<std::string> commandParts = splitString(command, " ");
	if (commandParts.size() == 0) {
		//TODO ERR_NORECIPIENT
		return;
	} else if (commandParts.size() == 1) {
		//TODO ERR_NOTEXTTOSEND
		return;
	}
	string target = commandParts[0];
	size_t pos = command.find(target);
	if (pos == std::string::npos) {
		//TODO ERR_NOTEXTTOSEND
		return;
	}
	string textToSend = command.substr(pos);
	if (*target.begin() == '#') {
		try {
			Channel *channel = server.getChannel(target);
			if (channel->getUser(fd) == NULL) {
				//TODO error not in channel ?
				return;
			}
			//TODO localhost might need to change
			string modifiedMsg = ":" + user->getNick() + "!" + user->getUsername() + "@" + "localhost PRIVMSG " + channel->getName() + " :" + textToSend + "\n";
			channel->sendMessage(user, modifiedMsg);
		} catch (std::exception &e) {
			cout << e.what() << endl;
			//TODO send err msg
		}
		//TODO send to channel
	} else if (*target.begin() == '$') {
		//TODO unknown? maybe this shouldn't be implemented?
	} else {
		//TODO send to user?
	}
}
