#ifndef COMMAND_INTERFACE_HPP
#define COMMAND_INTERFACE_HPP
class Server;
#include <string>
#include <sys/socket.h>
#include "../placeholders/Placeholder.hpp"
#include "../placeholders/Template.hpp"
#include "../constants/ErrorMessages.hpp"
#include "../constants/ReplyMessages.hpp"
#include "../helper_files/badFixHeader.hpp"

using namespace std;

class CommandInterface {
public:
	virtual std::string getName() const = 0;
	virtual void execute(Server &server, string &command, int fd) = 0;

	virtual ~CommandInterface() {}
};

#endif
