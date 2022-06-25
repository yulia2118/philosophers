# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fdarrin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/17 11:37:23 by fdarrin           #+#    #+#              #
#    Updated: 2021/04/10 15:32:38 by fdarrin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

CC = gcc

FLAGS = -Wall -Wextra -Werror

INCLUDES = includes

HEADER = philo_one.h

SRC = srcs/start.c\
        srcs/main.c \
        srcs/utils1.c \
		srcs/utils2.c

OBJ = $(SRC:.c=.o)

%.o: %.c $(HEADER)
		$(CC) -c $(FLAGS) -I $(INCLUDES) $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(OBJ) -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean:
		rm -rf $(OBJ) $(NAME)

re:		fclean all

.PHONY: clean fclean all re
