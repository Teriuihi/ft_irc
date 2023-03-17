#ifndef ERROR_MESSAGES_HPP
#define ERROR_MESSAGES_HPP
#include <string>

namespace ErrorMessages {
	const std::string ERR_UNKNOWN_COMMAND = ":<server_hostname> 421 <command> :Unknown command\n";
	const std::string ERR_PASSWDMISMATCH = ":<server_hostname> 464 :Password incorrect\n";
	const std::string ERR_BADCHANNELKEY = ":<server_hostname> 475 <channel> :Cannot join channel (+k)\n";
}
#endif
