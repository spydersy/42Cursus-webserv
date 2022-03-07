# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 21:33:12 by abelarif          #+#    #+#              #
#    Updated: 2022/02/18 16:42:30 by abelarif         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=   webserv

SERVER_SRCS=	./servers/servers.cpp\
				./servers/SocketInfos.cpp\
				./servers/Client.cpp\

REQUEST_SRCS=	./srcs/request/Request.cpp\
				./srcs/request/requestHandler.cpp\
				./srcs/request/Utils.cpp\
				./srcs/request/RequestLexer.cpp\

RESPONSE_SRCS=	./srcs/response/responseHandler.cpp\

PARSING_SRCS=	./srcs/confParsing/fileHandlerUtils.cpp\
				./srcs/confParsing/confParsing.cpp\
				./srcs/confParsing/positionHandler.cpp\
				./srcs/confParsing/fillData.cpp\

UTILS_SRCS=		./srcs/utils/errorStream.cpp\

SRCS=   		main.cpp\
				$(PARSING_SRCS)\
				$(UTILS_SRCS)\
				$(SERVER_SRCS)\
				$(REQUEST_SRCS)\
				$(RESPONSE_SRCS)\

OBJS=   $(SRCS:.cpp=.o)

CPPFLAGS =   -std=c++98 -Wall -Werror -Wextra
DEBUG =		 -std=c++98 -g3 -Wall -Werror -Wextra 

$(NAME):	$(OBJS)
		clang++ $(CPPFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

debug: $(OBJS)
	clang++ -g $(DEBUG) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re : fclean all
