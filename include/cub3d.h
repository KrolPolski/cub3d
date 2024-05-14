/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:58:21 by clundber          #+#    #+#             */
/*   Updated: 2024/05/14 16:09:03 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> 	// for printf, perror
# include <unistd.h> 	// for write, close, read
# include <fcntl.h>		// for open
# include <stdlib.h> 	// for malloc, free, exit
# include <string.h> 	// for strerror
# include "../Libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdbool.h>

# define BPP sizeof(int32_t)
void free_2d(char **ptr);
int get_rgba(int r, int g, int b, int a);

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
}	t_images;


typedef struct s_map
{
	char		**map;
	int			p_pos_x;
	int			p_pos_y;
	int			p_orient;

	char		*text[5]; //N->E->S->W

	int			*ceiling;
	int			*floor;
  	t_images  	*images; 
  	mlx_t		*mlx; 
 	 int		mapstart;
}	t_map;  






void	ft_nullfree(char *str);
int	 	cub3d_mlx(void);
int		parsing(int argc, char **argv, t_map *map);
int		ret_error(char *str);

#endif