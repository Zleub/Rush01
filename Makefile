# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adebray <adebray@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 10:50:05 by adebray           #+#    #+#              #
#    Updated: 2015/01/17 03:39:59 by adebray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_gkrellm

SRC			=	$(shell ls -1 ./src/*.cpp)

OBJ			=	$(SRC:.cpp=.o)

CC			=	g++
EXTRA		=	-Woverloaded-virtual
CCFLAGS		=	$(EXTRA) -Werror -Wall -Wextra -Iinc

SDLFLAG		=	-I/nfs/zfs-student-5/users/2013/adebray/.brew/include -L/nfs/zfs-student-5/users/2013/adebray/.brew/lib -lSDL2

all: $(NAME)

arnaud: $(OBJ)
			@$(CC) $(SDLFLAG) $(CCFLAGS) -o $(NAME) $(OBJ) main_arnaud.cpp
			@echo "\033[32m•\033[0m $(NAME) compil: \033[32m$(NAME)\033[0m"

arthur: $(OBJ)
			@$(CC) -o $(NAME) $(CCFLAGS) $(OBJ) main_arthur.cpp
			@echo "\033[32m•\033[0m $(NAME) compil: \033[32m$(NAME)\033[0m"

$(NAME): $(OBJ)
			@$(CC) -o $(NAME) $(CCFLAGS) $(OBJ) main.cpp
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

.PHONY: all clean fclean re $(NAME)
