#******************************************************************************#
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bmans <marvin@codam.nl>                      +#+                      #
#                                                    +#+                       #
#    Created: 2021/09/23 16:09:13 by bmans         #+#    #+#                  #
#    Updated: 2021/09/23 16:11:09 by bmans         ########   odam.nl          #
#                                                                              #
#******************************************************************************#

NAME = philo
SRC = 
CC = gcc
FLAGS = -Wall -Werror -Wextra

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all
