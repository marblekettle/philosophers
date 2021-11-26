# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bmans <marvin@codam.nl>                      +#+                      #
#                                                    +#+                       #
#    Created: 2021/09/23 16:09:13 by bmans         #+#    #+#                  #
#    Updated: 2021/11/26 11:11:38 by bmans         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = philo.c aux.c philosoph.c monitor.c
HEADER = philo.h
CC = gcc
FLAGS = -Wall -Werror -Wextra -g #-fsanitize=thread

$(NAME): $(SRC) $(HEADER)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)
	rm -rf $(NAME).dSYM

re: fclean all
