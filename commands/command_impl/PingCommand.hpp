#ifndef PING_COMMAND_HPP
#define PING_COMMAND_HPP
#include "../../helper_files/badFixHeader.hpp"

class PingCommand: public CommandInterface {
public:
	virtual string getName() const;
	virtual void execute(Server &server, string &command, int fd);
};


#endif