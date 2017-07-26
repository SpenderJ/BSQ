# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/26 14:33:05 by pguthaus          #+#    #+#              #
#    Updated: 2017/07/26 22:10:36 by dde-jesu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq

CC = CC# C compiler

CFLAGS = -I ./include/ -Wall -Werror -Wextra -g# C compiler flags

# Paths

SRCS =		src/bsq.c		\
			src/ds.c		\
			src/io.c		\
			src/parser.c	\
			src/matrix.c \
			src/error.c		\
			src/compress.c	\
			src/cli.c

OBJS = $(SRCS:.c=.o)

all:
			@make $(NAME)

$(NAME):	$(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

$(OUT_DIR):
	@echo "\033[1;33mCreating objects files directory..."
	@mkdir -p $(OUT_DIR)
	@echo "\033[1;32mObject files directory has been created !"

clean:
	@echo "\033[1;33mDeleting objects files..."
	@rm -rf $(OBJS)
	@echo "\033[1;32mObject files (based in 'src/') have been deleted !"

fclean: clean
	@echo "\033[1;33mDeleting executable..."
	@rm -f $(NAME)
	@echo "\033[1;32mThe executable '$(NAME)' has been deleted !"

licorne:
	@echo "\033[1;35mSearching for the universal answer..."
	@echo "\033[1;35mThe answer is... Hmmmmm... Maybe... No... OHHHH !!! The answer is: "
	@echo "🦄"

re: fclean all

.PHONY: re licorne fclean clean
