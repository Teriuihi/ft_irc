#ifndef MODE_COMMAND_HPP
#define MODE_COMMAND_HPP
#include "../../helper_files/badFixHeader.hpp"

class ModeCommand: public CommandInterface {
public:
	virtual string getName() const;
	virtual void execute(Server &server, string &command, int fd);
private:
	static void respondModeChannel(Server &server, string &channelName, string &userName, int fd, User *actor);

	static void setOp(Server &server, string &channelName, User *actor, string &affectedNick, bool state);
};

#endif
