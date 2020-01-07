# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lgutter <lgutter@student.codam.nl>           +#+                      #
#                                                    +#+                       #
#    Created: 2019/09/11 13:40:17 by lgutter        #+#    #+#                 #
#    Updated: 2020/01/07 13:46:30 by lgutter       ########   odam.nl          #
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
