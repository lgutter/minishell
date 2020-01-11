# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lgutter <lgutter@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/09/11 13:40:17 by lgutter        #+#    #+#                 #
#    Updated: 2020/01/11 14:06:40 by lgutter       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include srcs/minisrcs

JUNK = $(shell find -E . -regex ".*(\..*~|\#.*\#|\.DS_Store)" 2>/dev/null)

CSOURCES := $(MINISRCS:%= srcs/%.c)
OBJECTS := $(MINISRCS:%= srcs/%.o)

LIBFT := ft_printf/libftprintf.a
INCLPATH := -I ./incl -I ./ft_printf
HEADER := incl/minishell.h

CFLAGS := -Wall -Wextra -Werror -g

NAME := minishell

PLUS = \033[38;5;40m| + |\033[0;00m
MINUS = \033[38;5;160m| - |\033[0;00m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS) $(HEADER)
	@gcc $(MAIN) $(OBJECTS) $(CFLAGS) $(LIBFT) -o $@
	@echo "$(PLUS) compiled: $@"

$(LIBFT): FORCE
	@$(MAKE) -C ft_printf/

test: $(NAME)
	@$(MAKE) -C tests/

norm:
	@../norm.sh incl srcs Makefile

%.o: %.c
	@gcc -c $< $(CFLAGS) $(INCLPATH) -o $@
	@echo "$(PLUS) compiled: $@"

lclean:
	@rm -rfv $(JUNK) $(OBJECTS) | sed -E $$'s/(.*)/$(MINUS) removed: \\1/g'

clean: lclean
	@$(MAKE) clean -C tests/
	@$(MAKE) clean -C ft_printf/

lfclean: lclean
	@rm -rfv $(NAME) | sed -E $$'s/(.*)/$(MINUS) removed: \\1/g'

fclean: lfclean
	@$(MAKE) fclean -C tests/
	@$(MAKE) fclean -C ft_printf/

re: fclean all

FORCE:

.PHONY: all clean lclean lfclean fclean re FORCE
