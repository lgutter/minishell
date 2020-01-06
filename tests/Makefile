# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lgutter <lgutter@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/09/11 13:40:17 by lgutter        #+#    #+#                 #
#    Updated: 2020/01/06 15:15:06 by lgutter       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

include srcs/testsrcs

CSOURCES := $(TESTSRCS:%= srcs/%.c)
OBJECTS := $(TESTSRCS:%= srcs/%.o)

MINI := ../minishell
INCLPATH= -I ./incl -I ../incl -I ../ft_printf

CFLAGS = -Wall -Wextra

NAME := minitest

PLUS = \033[38;5;40m| + |\033[0;00m
MINUS = \033[38;5;160m| - |\033[0;00m

all: $(NAME)

$(NAME): $(MINI) $(OBJECTS)
	@$(CC) $(OBJECTS) $(CFLAGS) -o $@
	@echo "$(PLUS) $(NAME) has been compiled"

$(MINI): FORCE
	@$(MAKE) -C ../

%.o: %.c
	@$(CC) -c $< $(CFLAGS) $(INCLPATH) -o $@
	@echo "$(PLUS) $@ compiled"

clean:
	@rm -rf $(OBJECTS)
	@echo "$(MINUS) $(NAME) object files removed"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(MINUS) $(NAME) removed"

re: fclean all

FORCE:

.PHONY: all clean fclean re FORCE
