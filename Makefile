# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pguthaus <pguthaus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/26 14:33:05 by pguthaus          #+#    #+#              #
#    Updated: 2017/07/26 15:28:19 by pguthaus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bsq
CC = gcc# C compiler
CCFLAGS = -Wall -Werror -Wextra# C compiler flags
SRC_DIR = src# Base sources directory
OUT_DIR = out# Output directory
INC_DIR = include
LIB = $(OUT_DIR)/lib$(NAME).a

# Paths
SRCS = bsq.c ds.c io.c parser.c error.c
OBJS = $(SRCS:.c=.o)
OBJS_PATH = $(addprefix $(OUT_DIR)/, $(OBJS))
SRCS_PATH = $(addprefix $(SRC_DIR)/, $(SRCS))

all: $(NAME)

$(NAME): $(LIB)
	gcc $(CCFLAGS) -I$(INC_DIR) cli.c -o $(NAME) $(LIB)

$(OBJS_PATH): $(SRCS_PATH) $(OUT_DIR)
	$(CC) -c $< -o $@ $(CCFLAGS) -I$(INC_DIR)

$(OUT_DIR):
	@echo "\033[1;33mCreating objects files directory..."
	@mkdir -p $(OUT_DIR)
	@echo "\033[1;32mObject files directory has been created !"

$(LIB): $(OBJS_PATH)
	@echo "\033[1;32mCreating library..."
	ar rcs $(LIB) $(OBJS_PATH)
	@echo "\033[1;32mLibrary has been created !"

clean:
	@echo "\033[1;33mDeleting objects files..."
	@rm -rf out/
	@echo "\033[1;32mObject files (based in '$(OUT_DIR)') have been deleted !"

fclean: clean
	@echo "\033[1;33mDeleting executable..."
	@rm -f $(EXECUTABLE)
	@echo "\033[1;32mThe executable '$(EXECUTABLE)' has been deleted !"

licorne:
	@echo "\033[1;35mSearching for the universal answer..."
	@echo "\033[1;35mThe answer is... Hmmmmm... Maybe... No... OHHHH !!! The answer is: "
	@echo "🦄"
