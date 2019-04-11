# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kkostrub <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/25 12:17:13 by kkostrub          #+#    #+#              #
#    Updated: 2018/05/25 12:17:17 by kkostrub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRC = check.c\
	  main.c\
	  tetriminos.c\
	  coords.c\
	  square.c\
	  solve.c\
	  solve_instruments.c

INC = -Ifillit.h

OBJ = $(SRC:.c=.o)

LIBFT =	libft/libft.a

CC = gcc

FLAGS = -Wall -Wextra -Werror

.PHONY : all, re, clean, flcean

all: $(NAME)

$(OBJ): %.o: %.c
	$(CC) -c $(FLAGS) $< -o $@ $(INC)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LIBFT)

$(LIBFT):
		make -C libft

clean:
		rm -f $(OBJ)
			make clean -C libft

fclean: clean
		rm -f $(NAME)
			make fclean -C libft

re: fclean all