#ifndef ERROR_MESSAGES_HPP
#define ERROR_MESSAGES_HPP
#include <string>

namespace ErrorMessages {
	const std::string ERR_NOSUCHNICK = ":<server_hostname> 401 <nick> <channel> :No such nick\n";
	const std::string ERR_NOSUCHCHANNEL = ":<server_hostname> 403 <nick> <channel> :No such channel\n";
	const std::string ERR_NORECIPIENT = ":<server_hostname> 411 <nick> :No recipient given (<command>)\n";
	const std::string ERR_NOTEXTTOSEND = ":<server_hostname> 412 <nick> :No text to send\n";
	const std::string ERR_ERRONEUSNICKNAME = ":<server_hostname> 432 <nick> :Erroneous nickname\n";
	const std::string ERR_NICKNAMEINUSE = ":<server_hostname> 433 <nick> :Nickname is already in use\n";
	const std::string ERR_UNKNOWN_COMMAND = ":<server_hostname> 421 <nick> <command> :Unknown command\n";
	const std::string ERR_NOTREGISTERED  = ":<server_hostname> 451 * :You have not registered\n";
	const std::string ERR_ALREADYREGISTERED  = ":<server_hostname> 462 <nick> :You may not reregister\n";
	const std::string ERR_PASSWDMISMATCH = ":<server_hostname> 464 <nick> :Password incorrect\n";
	const std::string ERR_NEEDMOREPARAMS = ":<server_hostname> 461 <nick> <command> :Not enough parameters\n";
	const std::string ERR_ALREADYREGISTRED = ":<server_hostname> 462 <nick> :Unauthorized command (already registered)\n";
	const std::string ERR_BADCHANNELKEY = ":<server_hostname> 475 <nick> <channel> :Cannot join channel (+k)\n";
	const std::string ERR_CHANOPRIVSNEEDED = ":<server_hostname> 482 <nick> <channel> :You're not channel operator\n";
	const std::string ERR_USERSDONTMATCH = ":<server_hostname> 482 <nick> :Cant change mode for other users\n";
}
#endif
