#ifndef PRIV_MSG_COMMAND_HPP
#define PRIV_MSG_COMMAND_HPP
#include "../../helper_files/badFixHeader.hpp"

class PrivMsgCommand: public CommandInterface {
public:
	virtual string getName() const;
	virtual void execute(Server &server, string &command, int fd);
private:
	static void sendNoRecipientMessage(Server &server,User *user, string &command, int fd);
	static void sendNoTextToSendMessage(Server &server, User *user, int fd);
	static void sendChannelMessage(Server &server, int fd, const string &target, Template &channelMessageT, User *user);

	static void sendUserMessage(Server &server, User *actor, string const &target, Template &channelMessageT);
};

#endif
