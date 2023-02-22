/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccompote <ccompote@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 13:01:40 by ccompote          #+#    #+#             */
/*   Updated: 2023/01/14 13:01:46 by ccompote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_lines(int fd, t_game *zop)
{
	int		i;
	char	*str;

	i = 0;
	str = get_next_line(fd);
	if (str == NULL)
		return (0);
	zop->width = ft_strlen_no_nl(str);
	i++;
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		if (!str)
			break ;
		i++;
		if (ft_strlen_no_nl(str) != zop->width)
		{
			free(str);
			return (0);
		}	
	}
	zop->height = i;
	return (1);
}

void	create_map(int fd, t_game *zop, char **argv)
{
	int	i;

	zop->fd = open(argv[1], O_RDONLY);
	zop->map = malloc(sizeof(char *) * (zop->height + 1));
	i = 0;
	while (i < zop->height)
	{
		zop->map[i] = get_next_line(fd);
		i++;
	}
	zop->map[i] = NULL;
	close(zop->fd);
	zop->steps = 1;
}
