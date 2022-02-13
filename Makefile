# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 21:33:12 by abelarif          #+#    #+#              #
#    Updated: 2022/02/13 09:05:59 by abelarif         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=   webserv

REQUEST_SRCS=	./response/request/Requst.cpp\
				./response/request/Utils.cpp\
				./response/request/main.cpp\

PARSING_SRCS=	./srcs/confParsing/fileHandlerUtils.cpp\
				./srcs/confParsing/confParsing.cpp\
				./srcs/confParsing/positionHandler.cpp\
				./srcs/confParsing/fillData.cpp\

UTILS_SRCS=		./srcs/utils/errorStream.cpp\

SRCS=   		webserv.cpp\
				main.cpp\
				$(PARSING_SRCS)\
				$(UTILS_SRCS)\

OBJS=   $(SRCS:.cpp=.o)

CPPFLAGS=  -g3 #-Wall -Werror -Wextra -std=c++98 -fsanitize=address

$(NAME):	$(OBJS)
			clang++ $(CPPFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re : fclean all
