#include "ModeCommand.hpp"

string ModeCommand::getName() const {
	return "MODE";
}
//received command: {MODE} with content {#example}
//possible response :server 324 <nick> <channel> +tn
//	+tn should be the mode
//Another possible command for this could be something with an extra argument for what the mode change should be like:
//	MODE target [+|-][mode] [parameter(s)]
void ModeCommand::execute(Server &server, string &command, int fd) {
	//TODO check if this needs to be implemented
}
