#ifndef NICK_COMMAND_HPP
#define NICK_COMMAND_HPP
#include "../../helper_files/badFixHeader.hpp"

class NickCommand: public CommandInterface {
public:
	virtual string getName() const;
	virtual void execute(Server &server, string &command, int fd);
};


#endif
