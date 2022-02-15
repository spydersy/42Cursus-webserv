# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 21:33:12 by abelarif          #+#    #+#              #
#    Updated: 2022/02/14 22:35:59 by abelarif         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=   webserv

SERVER_SRCS=	./srcs/server/server.cpp\

REQUEST_SRCS=	./srcs/request/Request.cpp\
				./srcs/request/requestHandler.cpp\
				./srcs/request/Utils.cpp\

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

CPPFLAGS=   -std=c++98 -fsanitize=address -g3 -Wall -Werror -Wextra 

$(NAME):	$(OBJS)
			clang++ $(CPPFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re : fclean all
