# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lgutter <lgutter@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/09/11 13:40:17 by lgutter        #+#    #+#                 #
#    Updated: 2020/01/13 13:55:44 by lgutter       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include srcs/testsrcs
include ../srcs/minisrcs

OBJECTS := $(TESTSRCS:%= srcs/%.o)
OBJECTS += $(MINISRCS:%= ../srcs/%.o)

MINI := ../minishell
INCLPATH= -I ./incl -I ../incl -I ../ft_printf

CFLAGS = -Wall -Wextra
CRITERION := -L $(HOME)/.brew/lib -lcriterion

NAME := minitest
LIB := ../ft_printf/libftprintf.a

PLUS = \033[38;5;40m| + |\033[0;00m
MINUS = \033[38;5;160m| - |\033[0;00m

all: $(NAME)

$(NAME): $(MINI) $(OBJECTS) $(MINIOBJS)
	@$(CC) -coverage $(CRITERION) $(LIB) $(OBJECTS) $(CFLAGS) -o $@
	@echo "$(PLUS) compiled: $(NAME)"

$(MINI): FORCE
	@$(MAKE) -C ../

%.o: %.c
	@$(CC) -c $< $(CFLAGS) $(INCLPATH) -o $@
	@echo "$(PLUS) compiled: $@"

clean:
	@rm -rf $(OBJECTS)
	@rm -rfv $(OBJECTS) | sed -E $$'s/(.*)/$(MINUS) removed: \\1/g'

fclean: clean
	@rm -rfv $(NAME) | sed -E $$'s/(.*)/$(MINUS) removed: \\1/g'

re: fclean all

FORCE:

.PHONY: all clean fclean re FORCE
