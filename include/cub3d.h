/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:58:21 by clundber          #+#    #+#             */
/*   Updated: 2024/05/13 15:17:10 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h> 	// for printf, perror
# include <unistd.h> 	// for write, close, read
# include <fcntl.h>		// for open
# include <stdlib.h> 	// for malloc, free, exit
# include <string.h> 	// for strerror
# include "../MLX42/include/MLX42/MLX42.h"
# include "../Libft/libft.h"
#include <stdbool.h>

typedef struct s_map
{
	char	**map;
	int		p_pos_x;
	int		p_pos_y;
	int		p_orient;

	char	*ceiling;
	char	*floor;

	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;

	int		mapstart;
}	t_map;

int cub3d_mlx(void);
int	parsing(int argc, char **argv, t_map *map);
int	ret_error(char *str);


#endif