#include "ModeCommand.hpp"
std::vector<std::string> splitString(const std::string& str, const std::string &split);

string ModeCommand::getName() const {
	return "MODE";
}
//received command: {MODE} with content {#example}
//possible response :server 324 <nick> <channel> +tn
//	+tn should be the mode
//Another possible command for this could be something with an extra argument for what the mode change should be like:
//	MODE target [+|-][mode] [parameter(s)]
void ModeCommand::execute(Server &server, string &command, int fd) {
	User *user = server.getUser(fd);
	if (user == NULL || !user->isAuthed()) {
		//TODO ERROR
		return;
	}

	std::vector<std::string> commandParts = splitString(command, " ");
	if (commandParts.size() == 1) {
		respondModeChannel(server, command, fd);
	}
	//TODO implement setting modes
}

void ModeCommand::respondModeChannel(Server &server, string &channelName, int fd) {
	Channel* channel = server.getChannel(channelName);
	if (channel == NULL) {
		//TODO error
		return;
	}

	Template modeT = Template(ReplyMessages::RPL_CHANNELMODEIS);
	modeT.addPlaceholders(Placeholder("server_hostname", server.getHostname()));
	modeT.addPlaceholders(Placeholder("channel", channel->getName()));
	modeT.addPlaceholders(Placeholder("mode", "")); //Not in any modes
	modeT.addPlaceholders(Placeholder("mode params", "")); //No mode parameters

	string modeS = modeT.getString();
	send(fd, modeS.c_str(), modeS.size(), 0);
}
