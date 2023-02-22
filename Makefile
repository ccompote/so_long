# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 11:49:23 by ccompote          #+#    #+#              #
#    Updated: 2023/02/02 21:41:08 by ccompote         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
SRCS = main.c get_next_line.c get_next_line_utils.c check_map.c create_map.c action_right.c action_left.c\
		 action_down.c action_up_and_steps.c start_map.c another_check.c

NAME =  so_long
OBJ	= $(SRCS:.c=.o)
CFLAGS = -Wall -Werror -Wextra
LIBFT = ./libft
MLX42 = ./MLX42

all: libft MLX42 $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

MLX42:
	@$(MAKE) -C $(MLX42)

$(NAME): $(OBJ)
	$(CC) $(OBJ) MLX42/libmlx42.a $(LIBFT)/libft.a -I include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/" -o $(NAME)

clean:
	rm -f *.o
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(MLX42) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(MLX42) fclean

re: fclean all

.PHONY: all clean fclean re libft MLX42