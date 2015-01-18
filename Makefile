# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adebray <adebray@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 10:50:05 by adebray           #+#    #+#              #
#    Updated: 2015/01/18 05:53:46 by adebray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_gkrellm

SRC			=	$(shell ls -1 ./src/*.cpp)

OBJ			=	$(SRC:.cpp=.o)

CC			=	g++
MLXFLAG		=	-Lsrc/minilibx -lmlx -L/usr/X11/lib -lXext -lX11
EXTRA		=	-Woverloaded-virtual
CCFLAGS		=	-Iinc $(MLXFLAG) $(EXTRA) -Werror -Wall -Wextra

all: _minilibx $(NAME)

$(NAME): $(OBJ)
			@$(CC) -o $(NAME) $(CCFLAGS) $(OBJ) main.cpp
			@echo "\033[32m•\033[0m $(NAME) compil: \033[32m$(NAME)\033[0m"

_minilibx:
			@make -C src/minilibx 2> /dev/null

%.o: %.cpp
			@echo '.''\c'
			@$(CC) $(CCFLAGS) -o $@ -c $<

clean:
			@make -C src/minilibx clean
			@rm -f $(OBJ)
			@echo "\033[31m•\033[0m $(NAME) clean.\033[0m"

fclean:		clean
			@make -C src/minilibx fclean
			@rm -f $(NAME)
			@echo "\033[31m•\033[0m $(NAME) fclean: \033[31m$(NAME)\033[0m"

re:			fclean all

.PHONY: all clean fclean re $(NAME)
