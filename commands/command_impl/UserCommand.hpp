#ifndef USER_COMMAND_HPP
#define USER_COMMAND_HPP
#include "../../helper_files/badFixHeader.hpp"
#include "../../helper_files/messageReplies.hpp"

class UserCommand: public CommandInterface {
public:
	virtual string getName() const;
	virtual void execute(Server &server, string &command, int fd);
};


#endif
