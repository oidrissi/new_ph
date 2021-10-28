# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oidrissi <oidrissi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/28 21:21:25 by oidrissi          #+#    #+#              #
#    Updated: 2021/10/28 21:22:13 by oidrissi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = philo

SRC = philo.c\
	  routines.c\
	  philo_utils.c\
	  death_check.c\

all: $(NAME)

$(NAME): $(SRC)
	@$(CC) $(SRC) $(FLAGS) -o $(NAME)

fclean:
	@rm -rf $(NAME) $(NAMEB)

re: fclean all