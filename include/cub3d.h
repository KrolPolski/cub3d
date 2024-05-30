/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:58:21 by clundber          #+#    #+#             */
/*   Updated: 2024/05/30 13:29:28 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> 	// for printf, perror
# include <unistd.h> 	// for write, close, read
# include <fcntl.h>		// for open
# include <stdlib.h> 	// for malloc, free, exit
# include <string.h> 	// for strerror
# include <math.h>
# include "../Libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>
# include <limits.h>

# define BPP sizeof(int32_t)
# define DEG_2_RAD 0.01745329252

#ifndef M_PI
# define M_PI 3.14159265359 
# endif
typedef struct s_images
{
	mlx_image_t		*bg;
	mlx_texture_t	*black;
	mlx_texture_t	*white;
	mlx_texture_t	*player;
	mlx_texture_t	*direction;
	mlx_image_t		*blk;
	mlx_image_t		*wht;
	mlx_image_t		*plyr;
	mlx_image_t		*dir;
	mlx_image_t		*fg;
	mlx_image_t		*world;
}	t_images;

enum e_dir
{
	north,
	east,
	south,
	west,
	error,
};

typedef struct s_ray
{
	double	deg;
	int		row;
	double	ray_x;
	double	ray_y;
	double	dist;
	double	y_dist;
	double	x_dist;
}	t_ray;

typedef struct s_map
{
	char		**map;
	t_ray		*ray;
	int			p_pos_x;
	int			p_pos_y;
	double		p_orient;
	int			*ceiling;
	int			*floor;
	t_images	*images;
	mlx_t		*mlx;
	int			mapstart;
	char		*text[5]; //N->E->S->W
	bool		map_visible;
	int			rend_dist;
	int			s_width;
	int			s_height;
	int			proj_plane;
	double		fov_angle;
	int			map_x_border;
	int			map_y_border;
}	t_map;  

void	ray_caster(mlx_t *mlx, t_map *map, t_images *images);
char	detect_square(t_map *map, int x, int y);
void	ft_nullfree(char *str);
int		parsing(int argc, char **argv, t_map *map);
int		ret_error(char *str);
int		cub3d_mlx(t_map *map);
void	free_2d(char **ptr);
int		get_rgba(int r, int g, int b, int a);
#endif