/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:58:50 by rboudwin          #+#    #+#             */
/*   Updated: 2024/05/13 13:35:21 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_2d_map(mlx_t *mlx, t_map *map)
{
	mlx_image_t *bg;
	int			i;
	int			k;
	int			x;
	int			y;
	mlx_texture_t *black;
	mlx_texture_t *white;
	mlx_image_t *blk;
	mlx_image_t *wht;

	black = mlx_load_png("assets/black.png");
	white = mlx_load_png("assets/white.png");
	blk = mlx_texture_to_image(mlx, black);
	wht = mlx_texture_to_image(mlx, white);
	bg = mlx_new_image(mlx, 1366, 768);
	ft_memset(bg->pixels, 180, bg->width * bg->height * BPP);
	mlx_image_to_window(mlx, bg, 0, 0);
	i = 0;
	k = 0;
	x = 0;
	y = 0;
	//mlx_image_to_window(mlx, black, 500, 500);
	while (map->map[i])
	{
		while (map->map[i][k])
		{
			if (map->map[i][k] == '1')
			{
				printf("map->map[%d][%d] is %c so placing black img\n", i, k, map->map[i][k]);
				mlx_image_to_window(mlx, blk, (k + 2) * 64, (i + 2) * 64);
			}
			else if (map->map[i][k] == '0')
				mlx_image_to_window(mlx, wht, (k + 2) * 64, (i + 2) * 64);
			k++;
		}
		k = 0;
		i++;	
	}
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
	
	int i;
	i = 0;
	while (map.map[i])
	{
		printf("Line %d is: %s\n", i, map.map[i]);
		i++;
	}
		
	mlx = mlx_init(1366, 768, "cub3d", true);
	draw_2d_map(mlx, &map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_2d(map.map);
	return (EXIT_SUCCESS);
}