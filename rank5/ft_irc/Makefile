CXX     := c++
CXXFLAGS:= -Wall -Wextra -Werror -std=c++98 -g

# Executable name
NAME    := ircserv

# Source files
SRCS    := main.cpp Server.cpp Client.cpp Helpers.cpp Channel.cpp fillmessage.cpp

COMMANDS := ft_invite.cpp ft_kick.cpp ft_privmsg.cpp \
            ft_join.cpp ft_mode.cpp ft_topic.cpp ft_bot.cpp\

SRCS     += $(addprefix commands/, $(COMMANDS))

# Object files
OBJS    := $(SRCS:.cpp=.o)

# Header dependencies
HEADERS := Server.hpp Client.hpp

# Default target
all: $(NAME)

# Linking
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation rule
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJS)

# Clean everything
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all

.PHONY: all clean fclean re