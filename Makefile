# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/17 12:12:28 by afeuerst          #+#    #+#              #
#    Updated: 2017/11/11 17:40:37 by afeuerst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

NAME = 21sh

INCLUDE = -I ./includes -I ./functions/ft_printf/includes

#FLAGS = -O0 -g -Weverything
FLAGS = -O0 -g -Weverything -fsanitize=address
#FLAGS = -Wall -Wextra -Werror

C_SRC = $(shell find ./source -type f | grep "\.c")

LIB = ./functions/ft_printf/libftprintf.a -ltermcap

all:
	@make -j $(NAME)

$(NAME):
	@make -j -C functions/ft_printf
	@printf "\e[38;05;208mCompiling %s ..." $(NAME)
	@clang $(LIB) $(FLAGS) $(INCLUDE) $(C_SRC) -o $(NAME)
	@printf "\r\e[38;05;118m%s is now compiled !\n" $(NAME)

clean:
	@make clean -C functions/ft_printf
	@printf "\e[35m"

fclean: clean
	@make fclean -C functions/ft_printf
	@printf "\33[38;05;196m%s as been removed.\n" $(NAME)
	@rm -rf $(NAME)

re: fclean all
