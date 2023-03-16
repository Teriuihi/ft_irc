#ifndef PASSWORD_COMMAND_HPP
#define PASSWORD_COMMAND_HPP
#include "../../helper_files/badFixHeader.hpp"

class PasswordCommand: public CommandInterface {
public:
	virtual string getName() const;
	virtual void execute(Server &server, string &command, int fd);
};

#endif
