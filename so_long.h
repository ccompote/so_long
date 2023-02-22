/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:05:30 by ccompote          #+#    #+#             */
/*   Updated: 2023/01/13 21:29:54 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# define STEP 32
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

typedef struct struct_s
{
	mlx_image_t		*rat_image;
	mlx_texture_t	*rat_right_texture;
	mlx_texture_t	*rat_links_texture;
	mlx_texture_t	*rat_front_texture;
	mlx_texture_t	*rat_back_texture;
	mlx_image_t		*floor_image;
	mlx_texture_t	*floor_texture;
	mlx_image_t		*mushroom_image;
	mlx_texture_t	*mushroom_texture;
	mlx_image_t		*tree_image;
	mlx_texture_t	*tree_texture;
	mlx_image_t		*door_open_image;
	mlx_texture_t	*door_open_texture;
	mlx_image_t		*door_close_image;
	mlx_texture_t	*door_close_texture;
	mlx_t			*mlx;
	char			**map;
	int				points_begin;
	int				points_end;
	int				door_x;
	int				door_y;
	int				direction;
	int				width;
	int				height;
	int				steps;
	int				player_x;
	int				player_y;
	int				exit_x;
	int				exit_y;
	int				fd;
	int				exit_count;
	int				coll_count;
	int				start_count;
}	t_game;

char	*gn_strchr(char *s, int c);
char	*gn_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*ft_dup(char *str);
char	*ft_read(int fd, char *progress);
char	*ft_next_line(char *progress);
int		check_arg(int argc, char **argv);
int		check_items_present(t_game *zop);
int		ft_strlen_no_nl(char *s);
int		check_walls(t_game *zop);
int		check_path(int fd, t_game *zop);
void	freed(char **arr);
void	images_create(t_game *zop);
int		fill_images(t_game *zop, int x, int y);
void	end_game(t_game *zop);
void	print_steps(t_game *zop);
void	action_down(mlx_key_data_t keydata, void *param);
void	action_up(mlx_key_data_t keydata, void *param);
void	action_left(mlx_key_data_t keydata, void *param);
void	action_right(mlx_key_data_t keydata, void *param);
void	create_map(int fd, t_game *zop, char **argv);
int		map_lines(int fd, t_game *zop);

#endif