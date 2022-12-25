# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 11:49:23 by ccompote          #+#    #+#              #
#    Updated: 2022/12/19 19:53:27 by ccompote         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRCS = main.c get_next_line.c get_next_line_utils.c

NAME =  game
OBJ	= $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) MLX42/libmlx42.a -I include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 