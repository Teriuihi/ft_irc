#ifndef KICK_COMMAND_HPP
#define KICK_COMMAND_HPP
#include "../../helper_files/badFixHeader.hpp"

class KickCommand: public CommandInterface {
public:
	virtual string getName() const;

	virtual void execute(Server &server, string &command, int fd);
};


#endif
