/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 21:07:34 by ccompote          #+#    #+#             */
/*   Updated: 2023/01/13 22:53:49 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	right_c(t_game *zop, int x_temp, int y_temp)
{
	mlx_delete_image(zop->mlx, zop->rat_image);
	mlx_image_to_window(zop->mlx, zop->floor_image, x_temp + 32, y_temp);
	zop->map[(y_temp) / 32][(x_temp + 32) / 32] = '0';
	zop->rat_image = mlx_texture_to_image(zop->mlx, zop->rat_right_texture);
	mlx_image_to_window(zop->mlx, zop->rat_image, x_temp, y_temp);
	zop->points_end++;
}

void	right_move(t_game *zop, int x_temp, int y_temp)
{
	mlx_delete_image(zop->mlx, zop->rat_image);
	zop->rat_image = mlx_texture_to_image(zop->mlx, zop->rat_right_texture);
	zop->direction = 0;
	mlx_image_to_window(zop->mlx, zop->rat_image, x_temp, y_temp);
}

void	action_right(mlx_key_data_t keydata, void *param)
{
	t_game	*zop;
	int		x_temp;
	int		y_temp;

	zop = (t_game *) param;
	x_temp = zop->rat_image->instances->x;
	y_temp = zop->rat_image->instances->y;
	if (keydata.action == MLX_RELEASE)
	{
		if (zop->map[(y_temp) / 32][(x_temp + 32) / 32] == 'C')
			right_c(zop, x_temp, y_temp);
		if (zop->map[(y_temp) / 32][(x_temp + 32) / 32] != '1')
		{
			if (zop->direction != 0)
				right_move(zop, x_temp, y_temp);
			zop->rat_image->instances->x += 32;
			print_steps(zop);
		}
		if (zop->points_end == zop->points_begin)
			mlx_image_to_window(zop->mlx, zop->door_open_image,
				zop->door_x * 32, zop->door_y * 32);
		if ((zop->map[(y_temp) / 32][(x_temp + 32) / 32] == 'E')
			&& (zop->points_end == zop->points_begin))
			mlx_close_window(zop->mlx);
	}
}
