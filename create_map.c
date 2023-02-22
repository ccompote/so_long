/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 21:41:47 by ccompote          #+#    #+#             */
/*   Updated: 2023/01/14 13:07:37 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	images_create(t_game *zop)
{
	zop->rat_front_texture = mlx_load_png("images/rat_front.png");
	zop->rat_back_texture = mlx_load_png("images/rat_back.png");
	zop->rat_right_texture = mlx_load_png("images/rat_right.png");
	zop->rat_image = mlx_texture_to_image(zop->mlx, zop->rat_right_texture);
	zop->rat_links_texture = mlx_load_png("images/rat_links.png");
	zop->mushroom_texture = mlx_load_png("images/mushroom.png");
	zop->mushroom_image = mlx_texture_to_image(zop->mlx, zop->mushroom_texture);
	zop->tree_texture = mlx_load_png("images/tree.png");
	zop->tree_image = mlx_texture_to_image(zop->mlx, zop->tree_texture);
	zop->floor_texture = mlx_load_png("images/floor.png");
	zop->floor_image = mlx_texture_to_image(zop->mlx, zop->floor_texture);
	zop->door_open_texture = mlx_load_png("images/door_open.png");
	zop->door_open_image = mlx_texture_to_image(zop->mlx,
			zop->door_open_texture);
	zop->door_close_texture = mlx_load_png("images/door_close.png");
	zop->door_close_image = mlx_texture_to_image(zop->mlx,
			zop->door_close_texture);
	zop->direction = 5;
	zop->points_begin = 0;
	zop->points_end = 0;
}

void	fillin(t_game *zop, mlx_image_t *image, int i, int j)
{
	mlx_image_to_window(zop->mlx, zop->floor_image, j * STEP, i * STEP);
	mlx_image_to_window(zop->mlx, image, j * STEP, i * STEP);
	if (zop->map[i][j] == 'C')
		zop->points_begin++;
	if (zop->map[i][j] == 'E')
	{
		zop->door_x = j;
		zop->door_y = i;
	}
}

int	fill_images(t_game *zop, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	while (zop->map[++i])
	{
		j = -1;
		while (zop->map[i][++j] != '\n' && zop->map[i][j])
		{
			if (zop->map[i][j] == '1')
				fillin(zop, zop->tree_image, i, j);
			else if (zop->map[i][j] == 'C')
				fillin(zop, zop->mushroom_image, i, j);
			else if (zop->map[i][j] == 'E')
				fillin(zop, zop->door_close_image, i, j);
			else if (zop->map[i][j] == '0')
				mlx_image_to_window(zop->mlx, zop->floor_image,
					j * STEP, i * STEP);
			else if (zop->map[i][j] == 'P')
				fillin(zop, zop->rat_image, y, x);
			else
				return (0);
		}
	}
	return (1);
}

void	end_game(t_game *zop)
{
	mlx_terminate(zop->mlx);
	freed(zop->map);
	mlx_delete_texture(zop->door_close_texture);
	mlx_delete_texture(zop->door_open_texture);
	mlx_delete_texture(zop->tree_texture);
	mlx_delete_texture(zop->rat_right_texture);
	mlx_delete_texture(zop->rat_links_texture);
	mlx_delete_texture(zop->rat_back_texture);
	mlx_delete_texture(zop->rat_front_texture);
	mlx_delete_texture(zop->floor_texture);
	mlx_delete_texture(zop->mushroom_texture);
}
