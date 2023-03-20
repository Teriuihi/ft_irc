#ifndef TOPIC_HPP
#define TOPIC_HPP
#include "../../helper_files/badFixHeader.hpp"

class TopicCommand: public CommandInterface {
public:
	virtual string getName() const;

	virtual void execute(Server &server, string &command, int fd);
};


#endif
