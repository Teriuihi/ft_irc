#ifndef PRIV_MSG_COMMAND_HPP
#define PRIV_MSG_COMMAND_HPP
#include "../../helper_files/badFixHeader.hpp"

class PrivMsgCommand: public CommandInterface {
public:
	virtual string getName() const;

	virtual void execute(Server &server, string &command, int fd);
};

#endif
