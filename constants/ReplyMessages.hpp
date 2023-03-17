#ifndef REPLY_MESSAGES_HPP
#define REPLY_MESSAGES_HPP
#include <string>

namespace ReplyMessages {
	const std::string RPL_WELCOME = ":<server_hostname> 001 <nick> :Welcome to the Internet Relay Network <nick>!<user>@<host>\n";
	const std::string RPL_YOURHOST = ":<server_hostname> 002 <nick> :Your host is <servername>, running version <ver>\n";
	const std::string RPL_CREATED = ":<server_hostname> 003 <nick> :This server was created 16/03/2023\n";
	const std::string RPL_MYINFO = ":<server_hostname> 004 <nick> :<servername> <version> <available user modes> <available channel modes>\n";
	const std::string RPL_LIST =  ":<server_hostname> 322 <channel> <users> :<topic>\n";
	const std::string RPL_LISTEND =  ":<server_hostname> 323 :End of LIST\n";
	const std::string RPL_CHANNELMODEIS =  ":<server_hostname> 324 <channel> <mode> <mode params>\n";
	const std::string RPL_TOPIC = ":<server_hostname> 332 <channel> :<topic>\n";
	const std::string RPL_NAMREPLY = ":<server_hostname> 353 <channel> :<user_list>\n";
	const std::string RPL_ENDOFNAMES = ":<server_hostname> 366 <channel> :End of NAMES list\n";
	const std::string JOIN = ":<nick>!<username>@<hostname> JOIN <channel>\n";
	const std::string PRIVMSG =  ":<nick>!<user>@<host> PRIVMSG <channel> :<message>\n";
}
#endif
