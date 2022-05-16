# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 21:33:12 by abelarif          #+#    #+#              #
#    Updated: 2022/04/27 17:54:38 by mlachheb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=   webserv

SERVER_SRCS=	./servers/servers.cpp\
				./servers/SocketInfos.cpp\
				./servers/Client.cpp\

REQUEST_SRCS=	./srcs/request/Request.cpp\
				./srcs/request/Utils.cpp\
				./srcs/request/RequestLexer.cpp\

RESPONSE_SRCS=	./srcs/response/Response.Class.cpp\
				./srcs/response/CGI.Class.cpp\

PARSING_SRCS=	./srcs/confParsing/fileHandlerUtils.cpp\
				./srcs/confParsing/confParsing.cpp\
				./srcs/confParsing/positionHandler.cpp\
				./srcs/confParsing/fillData.cpp\
				./srcs/confParsing/Server.Class.cpp\
				./srcs/confParsing/Location.Class.cpp\

UTILS_SRCS=		./srcs/utils/errorStream.cpp\
				./srcs/utils/MimeTypes.Class.cpp\
				./srcs/utils/autoindex.Class.cpp\

SRCS=   		main.cpp\
				$(PARSING_SRCS)\
				$(UTILS_SRCS)\
				$(SERVER_SRCS)\
				$(REQUEST_SRCS)\
				$(RESPONSE_SRCS)\

OBJS=   $(SRCS:.cpp=.o)

CPPFLAGS= -Wall -Werror -Wextra -std=c++98

$(NAME):	$(OBJS)
			clang++ $(CPPFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re : fclean all
