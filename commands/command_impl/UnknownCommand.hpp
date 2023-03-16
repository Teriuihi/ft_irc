#ifndef UNKNOWN_COMMAND_HPP
#define UNKNOWN_COMMAND_HPP
#include "../../helper_files/badFixHeader.hpp"

class UnknownCommand: public CommandInterface {
public:
	virtual string getName() const;
	virtual void execute(Server &server, string &command, int fd);
};


#endif
