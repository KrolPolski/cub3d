/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:58:50 by rboudwin          #+#    #+#             */
/*   Updated: 2024/05/13 12:40:18 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_2d_map(mlx_t *mlx, t_map *map)
{
	mlx_image_t *bg;

	bg = mlx_new_image(mlx, 1366, 768);
	ft_memset(bg->pixels, 255, bg->width * bg->height * BPP);
	mlx_image_to_window(mlx, bg, 0, 0);
	map = (void *)map;
}
int cub3d_mlx(void)
{
	mlx_t	*mlx;
	t_map 	map;
	
	

	map.map = ft_calloc(10, sizeof(char *));
	map.map[0] = ft_strdup("111111111");
	map.map[1] = ft_strdup("100000001");
	map.map[2] = ft_strdup("100000001");
	map.map[3] = ft_strdup("100000001");
	map.map[4] = ft_strdup("100000001");
	map.map[5] = ft_strdup("100000001");
	map.map[6] = ft_strdup("100000001");
	map.map[7] = ft_strdup("100000001");
	map.map[8] = ft_strdup("111111111");
	map.map[9] = NULL;
	mlx = mlx_init(1366, 768, "cub3d", true);
	draw_2d_map(mlx, &map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_2d(map.map);
	return (EXIT_SUCCESS);
}