#ifndef REPLY_MESSAGES_HPP
#define REPLY_MESSAGES_HPP
#include <string>

namespace ReplyMessages {
	const std::string RPL_WELCOME = ":irc.example.com 001 <nick> :Welcome to the Internet Relay Network <nick>!<user>@<host>\n";
	const std::string RPL_YOURHOST = ":irc.example.com 002 <nick> :Your host is <servername>, running version <ver>\n";
	const std::string RPL_CREATED = ":irc.example.com 003 <nick> :This server was created 16/03/2023\n";
	const std::string RPL_MYINFO = ":irc.example.com 004 <nick> :<servername> <version> <available user modes> <available channel modes>\n";
}
#endif
