# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adebray <adebray@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 10:50:05 by adebray           #+#    #+#              #
#    Updated: 2015/01/16 22:53:43 by adebray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_gkrellm

SRC			=	$(shell ls -1 ./src/*.cpp)

OBJ			=	$(SRC:.cpp=.o)

CC			=	g++
EXTRA		=	-Woverloaded-virtual
CCFLAGS		=	$(EXTRA) -Werror -Wall -Wextra -Iinc
LIBFLAG		=	-lncurses

all: $(NAME)

$(NAME):	$(OBJ)
			@$(CC) $(LIBFLAG) -o $@ $(OBJ)
			@echo "\033[32m•\033[0m $(NAME) compil: \033[32m$(NAME)\033[0m"

%.o: %.cpp
			@echo '.''\c'
			@$(CC) $(CCFLAGS) -o $@ -c $<

clean:
			@rm -f $(OBJ)
			@echo "\033[31m•\033[0m $(NAME) clean.\033[0m"

fclean:		clean
			@rm -f $(NAME)
			@echo "\033[31m•\033[0m $(NAME) fclean: \033[31m$(NAME)\033[0m"

re:			fclean all

.PHONY: all clean fclean re
