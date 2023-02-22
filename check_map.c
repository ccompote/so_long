/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:42:12 by ccompote          #+#    #+#             */
/*   Updated: 2023/01/14 13:03:34 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	freed(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	fill(char **tab, t_game *zop, int pl_x, int pl_y)
{
	if (pl_y < 0 || pl_y >= zop->height || pl_x < 0
		|| pl_x >= zop->width || tab[pl_y][pl_x] != '0')
		return ;
	tab[pl_y][pl_x] = 'F';
	fill(tab, zop, pl_x - 1, pl_y);
	fill(tab, zop, pl_x + 1, pl_y);
	fill(tab, zop, pl_x, pl_y - 1);
	fill(tab, zop, pl_x, pl_y + 1);
}

void	new_change(char **new, t_game *zop)
{
	int	i;
	int	j;

	i = -1;
	while (new[++i])
	{
		j = -1;
		while (new[i][++j] != '\n' && new[i][j])
		{
			if (new[i][j] == 'E')
			{
				zop->exit_x = j;
				zop->exit_y = i;
				new[i][j] = '0';
			}
			else if (new[i][j] == 'P')
			{
				zop->player_x = j;
				zop->player_y = i;
				new[i][j] = '0';
			}
			else if (new[i][j] == 'C')
				new[i][j] = '0';
		}
	}
}

int	check_path(int fd, t_game *zop)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (zop->height + 1));
	while (i < zop->height)
	{
		new[i] = get_next_line(fd);
		i++;
	}
	new[i] = NULL;
	new_change(new, zop);
	fill(new, zop, zop->player_x, zop->player_y);
	if (new[zop->exit_y][zop->exit_x] != 'F')
	{
		i = -1;
		while (new[++i])
			free(new[i]);
		free(new);
		return (0);
	}
	i = 0;
	freed(new);
	return (1);
}
