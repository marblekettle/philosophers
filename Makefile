# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bmans <marvin@codam.nl>                      +#+                      #
#                                                    +#+                       #
#    Created: 2021/09/23 16:09:13 by bmans         #+#    #+#                  #
#    Updated: 2022/02/09 15:34:56 by bmans         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = philo.c aux.c #philosoph.c monitor.c
SRC_DIR = src
HEADER = philo.h
HEADER_DIR = includes
CC = gcc
FLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread

$(NAME): $(addprefix $(SRC_DIR)/,$(SRC)) $(addprefix $(HEADER_DIR)/,$(HEADER))
	$(CC) $(FLAGS) -I$(HEADER_DIR) $(addprefix $(SRC_DIR)/,$(SRC)) -o $(NAME)

all: $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM

re: fclean all

.PHONY: clean fclean re