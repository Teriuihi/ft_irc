#ifndef REPLY_MESSAGES_HPP
#define REPLY_MESSAGES_HPP
#include <string>

namespace ReplyMessages {
	const std::string RPL_WELCOME = ":irc.example.com 001 <nick> :Welcome to the Internet Relay Network <nick>!<user>@<host>\n";
	const std::string RPL_YOURHOST = ":irc.example.com 002 <nick> :Your host is <servername>, running version <ver>\n";
	const std::string RPL_CREATED = ":irc.example.com 003 <nick> :This server was created 16/03/2023\n";
	const std::string RPL_MYINFO = ":irc.example.com 004 <nick> :<servername> <version> <available user modes> <available channel modes>\n";
	const std::string JOIN = ":<nick>!<username>@<hostname> JOIN <channel>\n";
	const std::string RPL_TOPIC = ":irc.example.com 332 <channel> :<topic>\n";
	const std::string RPL_NAMREPLY = ":irc.example.com 353 <channel> :<user_list>\n";
	const std::string RPL_ENDOFNAMES = ":irc.example.com 366 <channel> :End of NAMES list\n";
}
#endif
