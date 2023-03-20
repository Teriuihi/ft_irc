#ifndef ERROR_MESSAGES_HPP
#define ERROR_MESSAGES_HPP
#include <string>

namespace ErrorMessages {
	const std::string ERR_NOSUCHCHANNEL = ":<server_hostname> 403 :<channel> :No such channel\n";
	const std::string ERR_NORECIPIENT = ":<server_hostname> 411 :No recipient given (<command>)\n";
	const std::string ERR_NOTEXTTOSEND = ":<server_hostname> 412 :No text to send\n";
	const std::string ERR_UNKNOWN_COMMAND = ":<server_hostname> 421 <command> :Unknown command\n";
	const std::string ERR_PASSWDMISMATCH = ":<server_hostname> 464 :Password incorrect\n";
	const std::string ERR_BADCHANNELKEY = ":<server_hostname> 475 <channel> :Cannot join channel (+k)\n";
	const std::string ERR_NEEDMOREPARAMS = ":<server_hostname> 461 <command> :Not enough parameters\n";
	const std::string ERR_ALREADYREGISTRED = ":<server_hostname> 462 :Unauthorized command (already registered)\n";
}
#endif
