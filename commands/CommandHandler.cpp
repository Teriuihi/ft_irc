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
