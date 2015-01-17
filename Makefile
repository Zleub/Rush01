# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adebray <adebray@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 10:50:05 by adebray           #+#    #+#              #
#    Updated: 2015/01/17 01:42:37 by adebray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ft_gkrellm

SRC			=	$(shell ls -1 ./src/*.cpp)

OBJ			=	$(SRC:.cpp=.o)

CC			=	g++
EXTRA		=	-Woverloaded-virtual
CCFLAGS		=	$(EXTRA) -Werror -Wall -Wextra -Iinc -I/nfs/zfs-student-5/users/2013/adebray/.brew/Cellar/sfml/2.1/include

SFMLFLAG	=	-L/nfs/zfs-student-5/users/2013/adebray/.brew/Cellar/sfml/2.1/lib -lsfml-graphics -lsfml-window -lsfml-system

all: $(NAME)

arnaud: $(OBJ)
			@echo $(DYLD_FALLBACK_LIBRARY_PATH)
 			ifndef DYLD_FALLBACK_LIBRARY_PATH
				@echo '\n'"Plz, export DYLD_FALLBACK_LIBRARY_PATH=~/.brew/lib in ordrer to get SFML to work"
 			else
				@$(CC) $(SFMLFLAG) -o $(NAME) $(OBJ) main_arnaud.cpp
				@echo "\033[32m•\033[0m $(NAME) compil: \033[32m$(NAME)\033[0m"
 			endif

arthur: $(OBJ)
			@$(CC) -o $(NAME) $(OBJ) main_arthur.cpp
			@echo "\033[32m•\033[0m $(NAME) compil: \033[32m$(NAME)\033[0m"

$(NAME): $(OBJ)
			@echo $(DYLD_FALLBACK_LIBRARY_PATH)
 			ifndef DYLD_FALLBACK_LIBRARY_PATH
				@echo '\n'"Plz, export DYLD_FALLBACK_LIBRARY_PATH=~/.brew/lib in ordrer to get SFML to work"
 			else
				@$(CC) $(SFMLFLAG) -o $(NAME) $(OBJ) main.cpp
				@echo "\033[32m•\033[0m $(NAME) compil: \033[32m$(NAME)\033[0m"
 			endif

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
