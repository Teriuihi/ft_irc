#ifndef LIST_COMMAND_HPP
#define LIST_COMMAND_HPP
#include "../../helper_files/badFixHeader.hpp"

class ListCommand: public CommandInterface {
public:
	virtual string getName() const;

	virtual void execute(Server &server, string &command, int fd);
};


#endif
