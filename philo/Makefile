# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 16:28:52 by zslowian          #+#    #+#              #
#    Updated: 2025/02/17 20:12:15 by zslowian         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread
RM = rm -f
CC = cc

SRC = clean.c \
	errors.c \
	get_set.c \
	init.c \
	logs.c \
	main.c \
	parse.c \
	start.c \
	sync.c \
	utils.c

OBJ = $(SRC:.c=.o)

%.o : %.c
	@$(CC) $(FLAGS) -c $< -o $@

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

hell: all
	valgrind --tool=helgrind -s ./philo 5 800 100 100 2

.PHONY: all clean fclean libft re	
