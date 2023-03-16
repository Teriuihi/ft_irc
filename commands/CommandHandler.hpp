#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <map>
#include <string>
#include "../helper_files/badFixHeader.hpp"

class CommandHandler {
public:
	CommandHandler();
	void execute(string& name, Server &server, std::string& command, int fd);
	virtual ~CommandHandler();
private:
	map<std::string, CommandInterface*> commands;
};

#endif