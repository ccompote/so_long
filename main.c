/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
/*   Updated: 2023/01/14 13:20:28 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	hook(void *param)
{
	t_game	*zop;

	zop = (t_game *) param;
	if (mlx_is_key_down(zop->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(zop->mlx);
	if (mlx_is_key_down(zop->mlx, MLX_KEY_W)
		|| mlx_is_key_down(zop->mlx, MLX_KEY_UP))
		mlx_key_hook(zop->mlx, action_up, param);
	if (mlx_is_key_down(zop->mlx, MLX_KEY_S)
		|| mlx_is_key_down(zop->mlx, MLX_KEY_DOWN))
		mlx_key_hook(zop->mlx, action_down, param);
	if (mlx_is_key_down(zop->mlx, MLX_KEY_A)
		|| mlx_is_key_down(zop->mlx, MLX_KEY_LEFT))
		mlx_key_hook(zop->mlx, action_left, param);
	if (mlx_is_key_down(zop->mlx, MLX_KEY_D)
		|| mlx_is_key_down(zop->mlx, MLX_KEY_RIGHT))
		mlx_key_hook(zop->mlx, action_right, param);
}

int	checker(t_game *zop, char **argv)
{
	zop->fd = open(argv[1], O_RDONLY);
	if (!check_items_present(zop))
	{
		ft_putstr_fd("Error\nWrong map\n", 1);
		freed(zop->map);
		close(zop->fd);
		return (1);
	}
	if (!check_walls(zop))
	{
		ft_putstr_fd("Error\nWrong map\n", 1);
		freed(zop->map);
		close(zop->fd);
		return (1);
	}
	if (!check_path(zop->fd, zop))
	{
		ft_putstr_fd("Error\nWrong map\n", 1);
		freed(zop->map);
		close(zop->fd);
		return (1);
	}
	close(zop->fd);
	return (0);
}

int	checker_2(t_game *zop, char **argv)
{
	zop->fd = open(argv[1], O_RDONLY);
	if (zop->fd == -1)
	{
		ft_putstr_fd("Map file not readable\n", 1);
		close(zop->fd);
		return (1);
	}
	if (!map_lines(zop->fd, zop))
	{
		ft_putstr_fd("Error\nWrong map\n", 1);
		close(zop->fd);
		return (1);
	}
	close(zop->fd);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	zop;

	if (!check_arg(argc, argv) || checker_2(&zop, argv))
		return (0);
	create_map(zop.fd, &zop, argv);
	if (checker(&zop, argv))
		return (0);
	zop.mlx = mlx_init(zop.width * STEP, zop.height * STEP, "MLX42", true);
	if (!zop.mlx)
		exit(EXIT_FAILURE);
	images_create(&zop);
	if (!fill_images(&zop, zop.player_x, zop.player_y))
	{
		ft_putstr_fd("Wrong map\n", 1);
		end_game(&zop);
		return (0);
	}
	mlx_loop_hook(zop.mlx, &hook, &zop);
	mlx_loop(zop.mlx);
	end_game(&zop);
	return (EXIT_SUCCESS);
}
