#ifndef QUIT_COMMAND_HPP
#define QUIT_COMMAND_HPP
#include "../../helper_files/badFixHeader.hpp"

class QuitCommand: public CommandInterface {
public:
	virtual string getName() const;
	virtual void execute(Server &server, string &command, int fd);
};


#endif
