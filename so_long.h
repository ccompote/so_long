#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "MLX42/include/MLX42/MLX42.h"

typedef struct struct_s
{
	mlx_image_t		*snail_image;
	mlx_texture_t	*snail_texture;
	mlx_image_t		*wall_image;
	mlx_texture_t	*wall_texture;
	mlx_image_t		*mushroom_image;
	mlx_texture_t	*mushroom_texture;
	mlx_t			*mlx;
	char			**map;
}	t_game;

size_t	ft_strlen(char *s);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*ft_dup(char *str);
char	*ft_read(int fd, char *progress);
char	*ft_next_line(char *progress);

#endif