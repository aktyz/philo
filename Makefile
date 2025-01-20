# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 16:28:52 by zslowian          #+#    #+#              #
#    Updated: 2025/01/20 14:43:38 by zslowian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
FLAGS = -Wall -Wextra -Werror
RM = rm -f
CC = cc

SRC = main.c \
	clean.c \
	errors.c \
	init.c \
	logs.c \
	philo_tasks.c \
	routines.c \
	utils.c

OBJ = $(SRC:.c=.o)

%.o : %.c
	@$(CC) $(FLAGS) -c $< -o $@ -g -pthread

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJ)

debug: $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME) -g -pthread

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean libft re	
