#ifndef JOIN_COMMAND_HPP
#define JOIN_COMMAND_HPP
#include "../../helper_files/badFixHeader.hpp"

class JoinCommand: public CommandInterface {
public:
	virtual string getName() const;
	virtual void execute(Server &server, string &command, int fd);
};

#endif
