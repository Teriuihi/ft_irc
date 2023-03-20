#include "CommandHandler.hpp"
#include "command_impl/UserCommand.hpp"
#include "command_impl/UnknownCommand.hpp"
#include "command_impl/JoinCommand.hpp"
#include "command_impl/PingCommand.hpp"
#include "command_impl/PasswordCommand.hpp"
#include "command_impl/NickCommand.hpp"
#include "command_impl/PrivMsgCommand.hpp"
#include "command_impl/ModeCommand.hpp"
#include "command_impl/PartCommand.hpp"
#include "command_impl/QuitCommand.hpp"
#include "command_impl/ListCommand.hpp"
#include "command_impl/KickCommand.hpp"
#include "command_impl/OperCommand.hpp"

CommandHandler::CommandHandler() {
	this->commands.insert(std::make_pair("PASS", new PasswordCommand()));
	this->commands.insert(std::make_pair("USER", new UserCommand()));
	this->commands.insert(std::make_pair("UNKNOWN", new UnknownCommand()));
	this->commands.insert(std::make_pair("JOIN", new JoinCommand()));
	this->commands.insert(std::make_pair("PING", new PingCommand()));
	this->commands.insert(std::make_pair("NICK", new NickCommand()));
	this->commands.insert(std::make_pair("PRIVMSG", new PrivMsgCommand()));
	this->commands.insert(std::make_pair("MODE", new ModeCommand()));
	this->commands.insert(std::make_pair("PART", new PartCommand()));
	this->commands.insert(std::make_pair("QUIT", new QuitCommand()));
	this->commands.insert(std::make_pair("LIST", new ListCommand()));
	this->commands.insert(std::make_pair("KICK", new KickCommand()));
	this->commands.insert(std::make_pair("OPER", new OperCommand()));
	//TODO add OPER command
	//3.1.4 Oper message
	//
	//      Command: OPER
	//   Parameters: <name> <password>
	//
	//   A normal user uses the OPER command to obtain operator privileges.
	//   The combination of <name> and <password> are REQUIRED to gain
	//   Operator privileges.  Upon success, the user will receive a MODE
	//   message (see section 3.1.5) indicating the new user modes.
	//
	//   Numeric Replies:
	//
	//           ERR_NEEDMOREPARAMS              RPL_YOUREOPER
	//           ERR_NOOPERHOST                  ERR_PASSWDMISMATCH
	//
	//   Example:
	//
	//   OPER foo bar                    ; Attempt to register as an operator
	//                                   using a username of "foo" and "bar"
	//                                   as the password.
	//TODO add TOPIC as an OP command
}

void CommandHandler::execute(string &name, Server &server, string &command, int fd) {
	std::map<std::string, CommandInterface*>::iterator it;
	if (std::equal(name.begin(), name.end(), "CAP"))
		return;
	it = commands.find(name);
	if (it != commands.end()) {
		it->second->execute(server, command, fd);
	} else if (!std::equal(name.begin(), name.end(), "UNKNOWN")) {
		//As an exception this gets the name + command of the executed command back to it so it can report to the client what the wrong command was
		std::string tmp = "UNKNOWN";
		execute(tmp, server, name.append(" " + command), fd);
	}
}

CommandHandler::~CommandHandler() {
	std::map<std::string, CommandInterface*>::iterator it;
	it = commands.begin();
	while (it != commands.end()) {
		delete it->second;
		it++;
	}
}
