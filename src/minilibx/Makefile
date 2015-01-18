##
## Makefile for MiniLibX in /home/boulon/work/c/raytraceur/minilibx
##
## Made by Olivier Crouzet
## Login   <ol@epitech.net>
##
## Started on  Tue Oct  5 15:56:43 2004 Olivier Crouzet
## Last update Tue May 15 15:44:41 2007 Olivier Crouzet
##

## Please use configure script


all	: do_configure

do_configure	:
	@./configure
	@echo "\033[32m•\033[0m compil: \033[32mlibmlx.a\033[0m"

clean	:
	@./configure clean

fclean	: clean
	@rm -f libmlx.a
	@rm -f libmlx_x86_64.a
	@echo "\033[31m•\033[0m fclean: \033[31mlibmlx.a\033[0m"


re	: clean all
