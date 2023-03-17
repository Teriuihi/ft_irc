#ifndef PART_COMMAND_HPP
#define PART_COMMAND_HPP
#include "../../helper_files/badFixHeader.hpp"

class PartCommand: public CommandInterface {
public:
	virtual string getName() const;
	virtual void execute(Server &server, string &command, int fd);
};

#endif
