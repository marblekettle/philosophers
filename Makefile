# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bmans <marvin@codam.nl>                      +#+                      #
#                                                    +#+                       #
#    Created: 2021/09/23 16:09:13 by bmans         #+#    #+#                  #
#    Updated: 2021/10/11 11:56:31 by bmans         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = philo.c aux.c philosoph.c monitor.c
HEADER = philo.h
CC = gcc
FLAGS = -Wall -Werror -Wextra -g

$(NAME): $(SRC) $(HEADER)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all
