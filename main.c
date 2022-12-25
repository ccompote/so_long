/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
/*   Updated: 2022/12/24 20:01:59 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/include/MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include "so_long.h"
#define WIDTH 11
#define HEIGHT 6
#define STEP 32

//mlx_image_t	*g_img;

int map_lines(int fd)
{
	int i;
	char *str;
	
	i = 0;
	while ((str = get_next_line(fd)))
	{
		i++;
		free(str);
	}
	return (i);
}

void create_map(int fd, int lines, t_game *zop)
{
	int i;
	// char **map;

	zop->map = malloc(sizeof(char *) * (lines + 1));
	i = 0;
	while(i < lines)
	{
		zop->map[i] = get_next_line(fd);
		i++;
	}
	zop->map[i] = NULL;
	// return (map);
}

int player_get_x(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				return (j);
			j++;
		}
		i++;
	}	
	return (-1);
}

int player_get_y(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				return (i);
			j++;
		}
		i++;
	}	
	return (-1);
}

int mushroom_get_x(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				return (j);
			j++;
		}
		i++;
	}	
	return (-1);
}

int mushroom_get_y(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				return (i);
			j++;
		}
		i++;
	}	
	return (-1);
}

int wall_get_x(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				return (j);
			j++;
		}
		i++;
	}	
	return (-1);
}

int wall_get_y(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '1')
				return (i);
			j++;
		}
		i++;
	}	
	return (-1);
}


void action_up(mlx_key_data_t keydata, void *param)
{
	t_game *zop;

	zop = (t_game *) param;

	if(keydata.action == MLX_RELEASE)
	{
		if (zop->map[(zop->snail_image->instances[0].y - 32) / 32][(zop->snail_image->instances[0].x) / 32] != '1')
			zop->snail_image->instances[0].y -= 32;
	}
}

void action_down(mlx_key_data_t keydata, void *param)
{
	t_game *zop;
	int	x_temp;
	int y_temp;

	zop = (t_game *) param;
	x_temp = zop->snail_image->instances->x;
	y_temp = zop->snail_image->instances->y;
	if(keydata.action == MLX_RELEASE)
	{
		
		if (zop->map[(y_temp + 32) / 32][(x_temp) / 32] == 'C')
		{
			mlx_delete_image(zop->mlx, zop->snail_image);
			mlx_image_to_window(zop->mlx, zop->wall_image, x_temp , y_temp + 32); //change for floor
			zop->map[(y_temp + 32) / 32][(x_temp) / 32] = '0';
			zop->snail_image = mlx_texture_to_image(zop->mlx, zop->snail_texture);
			mlx_image_to_window(zop->mlx, zop->snail_image, x_temp , y_temp);
		}
		if (zop->map[(y_temp + 32) / 32][(x_temp) / 32] != '1')
			zop->snail_image->instances[0].y += 32;
	}
}

void action_left(mlx_key_data_t keydata, void *param)
{
	t_game *zop;

	zop = (t_game *) param;
	if(keydata.action == MLX_RELEASE)
	{
		if (zop->map[(zop->snail_image->instances->y) / 32][(zop->snail_image->instances->x - 32) / 32] == 'C')
		{
			zop->map[(zop->snail_image->instances->y) / 32][(zop->snail_image->instances->x - 32) / 32] = '0';
			//delete image
			mlx_image_to_window(zop->mlx, zop->wall_image, zop->snail_image->instances->x - 32, zop->snail_image->instances->y);
			
		}
		if (zop->map[(zop->snail_image->instances->y) / 32][(zop->snail_image->instances->x - 32) / 32] != '1')
			zop->snail_image->instances->x -= 32;
	}
}

void action_right(mlx_key_data_t keydata, void *param)
{
	t_game *zop;

	zop = (t_game *) param;
	if(keydata.action == MLX_RELEASE)
	{
		if (zop->map[(zop->snail_image->instances[0].y) / 32][(zop->snail_image->instances[0].x + 32) / 32] != '1')
			zop->snail_image->instances[0].x += 32;
	}
}

//key_hook
void	hook(void *param)
{
	t_game *zop;
	
	zop = (t_game *) param;
	if (mlx_is_key_down(zop->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(zop->mlx);
	if (mlx_is_key_down(zop->mlx, MLX_KEY_W) || mlx_is_key_down(zop->mlx, MLX_KEY_UP))
		mlx_key_hook(zop->mlx, action_up, param);
	if (mlx_is_key_down(zop->mlx, MLX_KEY_S) || mlx_is_key_down(zop->mlx, MLX_KEY_DOWN))
		mlx_key_hook(zop->mlx, action_down, param);
	if (mlx_is_key_down(zop->mlx, MLX_KEY_A) || mlx_is_key_down(zop->mlx, MLX_KEY_LEFT))
		mlx_key_hook(zop->mlx, action_left, param);
	if (mlx_is_key_down(zop->mlx, MLX_KEY_D) || mlx_is_key_down(zop->mlx, MLX_KEY_RIGHT))
		mlx_key_hook(zop->mlx, action_right, param);
}

void	checkleaks(void)
{
	system("leaks game");
}

int32_t	main(void)
{

	int fd;
	int i;
	int f;
	int count;
	t_game zop;
	atexit(checkleaks);
	i = 0;
	f = 0;
	count = 0;
	int j;
	fd = open("map.ber", O_RDONLY);
	j = map_lines(fd);
	close(fd);
	fd = open("map.ber", O_RDONLY);
	create_map(fd, j, &zop);
	close(fd);
	// i = 0;
	// while(zop.map[i])
	// {
	// 	printf("%s",zop.map[i]);
	// 	i++;
	// }
	zop.mlx = mlx_init(WIDTH * STEP, HEIGHT * STEP, "MLX42", true);
	if (!zop.mlx)
		exit(EXIT_FAILURE);
	zop.snail_texture = mlx_load_png("snail.png");
	zop.snail_image = mlx_texture_to_image(zop.mlx, zop.snail_texture);
	zop.mushroom_texture = mlx_load_png("mushroom.png");
	zop.mushroom_image = mlx_texture_to_image(zop.mlx, zop.mushroom_texture);
	zop.wall_texture = mlx_load_png("wall.png");
	zop.wall_image = mlx_texture_to_image(zop.mlx, zop.wall_texture);
	int player_y = player_get_y(zop.map);
	int player_x = player_get_x(zop.map);
	i = 0;
	j = 0;
	while (zop.map[i])
	{
		j = 0;
		while (zop.map[i][j])
		{
			if (zop.map[i][j] == '1')
			{
				mlx_image_to_window(zop.mlx, zop.wall_image, j * STEP, i * STEP);
			}
			else if (zop.map[i][j] == 'C')
				mlx_image_to_window(zop.mlx, zop.mushroom_image, j * STEP, i * STEP);
			j++;
		}
		i++;
	}
	mlx_image_to_window(zop.mlx, zop.snail_image, player_x * STEP, player_y * STEP);
	
	mlx_loop_hook(zop.mlx, &hook, &zop);
	mlx_loop(zop.mlx);
	mlx_terminate(zop.mlx);
	i = 0;
	while (zop.map[i])
	{
		free(zop.map[i]);
		i++;
	}
	free(zop.map);
	return (EXIT_SUCCESS);
}