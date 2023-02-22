/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:03:13 by ccompote          #+#    #+#             */
/*   Updated: 2023/01/14 13:03:37 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_arg(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
	{
		ft_putstr_fd("Wrong argument\n", 1);
		return (0);
	}
	while (argv[1][i])
		i++;
	i = i - 4;
	if (ft_strncmp(".ber", &argv[1][i], 4) != 0)
	{
		ft_putstr_fd("Wrong argument\n", 1);
		return (0);
	}
	return (1);
}

int	check_items_present(t_game *zop)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (zop->map[i])
	{
		j = 0;
		while (zop->map[i][j] != '\n' && zop->map[i][j])
		{
			if (zop->map[i][j] == 'E')
				zop->exit_count++;
			else if (zop->map[i][j] == 'C')
				zop->coll_count++;
			else if (zop->map[i][j] == 'P')
				zop->start_count++;
			j++;
		}
		i++;
	}
	if (zop->exit_count != 1 || zop->start_count != 1 || zop->coll_count == 0)
		return (0);
	return (1);
}

int	check_walls(t_game *zop)
{
	int	i;
	int	j;

	j = 0;
	while (j != zop->width)
	{
		if (zop->map[0][j] == '1' && zop->map[zop->height - 1][j] == '1')
			j++;
		else
			return (0);
	}
	i = 0;
	while (zop->map[i])
	{
		if (zop->map[i][0] == '1' && zop->map[i][zop->width - 1] == '1')
			i++;
		else
			return (0);
	}
	return (1);
}
