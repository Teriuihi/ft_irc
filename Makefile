NAME=ft_irc
CC=c++
FLAGS=-Wall -Wextra -Werror -std=c++98
RM=rm -f

FILES=main.cpp helper_files/messageReplies.cpp helper_files/util.cpp placeholders/Template.cpp commands/CommandHandler.cpp commands/command_impl/PingCommand.cpp commands/command_impl/PasswordCommand.cpp commands/command_impl/JoinCommand.cpp commands/command_impl/UnknownCommand.cpp commands/command_impl/UserCommand.cpp irc_data/Server.cpp irc_data/Channel.cpp irc_data/User.cpp
HEADERS=BST/BSTree.hpp BST/Node.hpp helper_files/static_variables.hpp helper_files/messageReplies.hpp placeholders/Template.hpp placeholders/Placeholder.hpp commands/CommandInterface.hpp commands/command_impl/PasswordCommand.hpp commands/CommandHandler.hpp commands/command_impl/UserCommand.hpp commands/command_impl/PingCommand.hpp commands/command_impl/JoinCommand.hpp commands/command_impl/UnknownCommand.hpp constants/ReplyMessages.hpp constants/ErrorMessages.hpp irc_data/User.hpp irc_data/Server.hpp irc_data/Channel.hpp

OBJ=$(FILES:%.cpp=%.o)

%.o: %.cpp $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: make all clean fclean re
