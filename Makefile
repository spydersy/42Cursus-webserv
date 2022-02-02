# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 21:33:12 by abelarif          #+#    #+#              #
#    Updated: 2022/02/02 22:57:56 by abelarif         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=   webserv

PARSING_SRCS=	./srcs/confParsing/confParsing.cpp\

UTILS_SRCS=		./srcs/utils/errorStream.cpp\

SRCS=   webserv.cpp\
		main.cpp\
		$(PARSING_SRCS)\
		$(UTILS_SRCS)\

OBJS=   $(SRCS:.cpp=.o)

CPPFLAGS=  -Wall -Werror -Wextra #-std=c++98

$(NAME):	$(OBJS)
			clang++ $(CPPFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re : fclean all