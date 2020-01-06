# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lgutter <lgutter@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/09/11 13:40:17 by lgutter        #+#    #+#                 #
#    Updated: 2020/01/06 15:36:56 by lgutter       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include srcs/minisrcs

JUNK = $(shell find -E . -regex ".*(\..*~|\#.*\#|\.DS_Store)" 2>/dev/null)

MAIN := srcs/main.o
CSOURCES := $(MINISRCS:%= srcs/%.c)
OBJECTS := $(MINISRCS:%= srcs/%.o)

LIBFT := ft_printf/libftprintf.a
INCLPATH=-I ./incl -I ./ft_printf
HEADER := incl/minishell.h

CFLAGS = -Wall -Wextra -Werror -g

NAME := minishell
TEST := minitest

PLUS = \033[38;5;40m| + |\033[0;00m
MINUS = \033[38;5;160m| - |\033[0;00m

all: $(NAME)

$(NAME): $(LIBFT) $(MAIN) $(OBJECTS) $(HEADER)
	@$(CC) $(MAIN) $(OBJECTS) $(CFLAGS) $(LIBFT) -o $@
	@echo "$(PLUS) $(NAME) has been compiled"

$(LIBFT): FORCE
	@$(MAKE) -C ft_printf/

$(TEST): $(NAME)
	@$(MAKE) -C tests/

%.o: %.c
	@$(CC) -c $< $(CFLAGS) $(INCLPATH) -o $@
	@echo "$(PLUS) $@ compiled"

clean:
	@rm -rf $(JUNK)
	@echo "$(MINUS) Junk files removed"
	@rm -rf $(OBJECTS) $(MAIN:%.c= %.o)
	@echo "$(MINUS) $(NAME) object files removed"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(MINUS) $(NAME) removed"
	@$(MAKE) fclean -C tests/
	@$(MAKE) fclean -C ft_printf/

re: fclean all

FORCE:

.PHONY: all clean fclean re FORCE
