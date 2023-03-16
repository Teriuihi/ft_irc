#include "CommandHandler.hpp"
#include "command_impl/UserCommand.hpp"
#include "command_impl/UnknownCommand.hpp"
#include "command_impl/JoinCommand.hpp"
#include "command_impl/PingCommand.hpp"
#include "command_impl/PasswordCommand.hpp"

CommandHandler::CommandHandler() {
	//TODO add PRIVMSG
	//	received command: {PRIVMSG} with content {#example :cool}
	//TODO add PART
	//	received command: {PART} with content {#example :Closing Window}
	//TODO do I need to add MODE?
	//	received command: {MODE} with content {#example}
	//TODO add QUIT
	//	received command: {QUIT} with content {:Going offline, see ya! (www.adiirc.com)}
	this->commands.insert(std::make_pair("PASS", new PasswordCommand()));
	this->commands.insert(std::make_pair("USER", new UserCommand()));
	this->commands.insert(std::make_pair("UNKNOWN", new UnknownCommand()));
	this->commands.insert(std::make_pair("JOIN", new JoinCommand()));
	this->commands.insert(std::make_pair("PING", new PingCommand()));
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
		execute(tmp, server, name.append(command), fd);
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
