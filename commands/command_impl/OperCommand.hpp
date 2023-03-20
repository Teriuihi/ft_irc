#ifndef OPER_COMMAND_HPP
#define OPER_COMMAND_HPP
#include "../../helper_files/badFixHeader.hpp"

class OperCommand: public CommandInterface {
public:
	virtual string getName() const;
	virtual void execute(Server &server, string &command, int fd);
};


#endif
