/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:58:21 by clundber          #+#    #+#             */
/*   Updated: 2024/05/13 12:38:42 by rboudwin         ###   ########.fr       */
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

# define BPP sizeof(int32_t)
int cub3d_mlx(void);
void free_2d(char **ptr);

typedef struct s_map
{
	char	**map;
	int		p_pos_x;
	int		p_pos_y;
	int		p_orient;

	int		*ceiling;
	int		*floor;

	char	*no_text;
	char	*so_text;
	char	*we_text;
	char	*ea_text;

}	t_map;

#endif