/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:58:50 by rboudwin          #+#    #+#             */
/*   Updated: 2024/05/13 12:14:05 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_2d_map(mlx_t *mlx, char **map)
{
	
}
int cub3d_mlx(void)
{
	mlx_t	*mlx;
	char	**map;

	map = ft_calloc(10, sizeof(char *));
	map[0] = ft_strdup("111111111");
	map[1] = ft_strdup("100000001");
	map[2] = ft_strdup("100000001");
	map[3] = ft_strdup("100000001");
	map[4] = ft_strdup("100000001");
	map[5] = ft_strdup("100000001");
	map[6] = ft_strdup("100000001");
	map[7] = ft_strdup("100000001");
	map[8] = ft_strdup("111111111");
	map[9] = NULL;
	mlx = mlx_init(1366, 768, "cub3d", true);
	draw_2d_map(mlx, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_2d(map);
	return (EXIT_SUCCESS);
}