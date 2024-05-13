/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:58:50 by rboudwin          #+#    #+#             */
/*   Updated: 2024/05/13 18:00:35 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_direction(mlx_t *mlx, t_map *map, t_images *images)
{
	int i;
	(void)mlx;
	(void)map;
	i = 0;
	mlx_delete_image(mlx, images->plyr);
	images->plyr = mlx_texture_to_image(mlx, images->player);
	mlx_image_to_window(mlx, images->plyr, map->p_pos_x, map->p_pos_y);
	while (i < 30)
	{
		printf("attempting to draw direction\n");
		//this draws straight north
		//mlx_put_pixel(images->plyr, images->plyr->width / 2, i, get_rgba(255, 0, 0, 255));
		mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient), images->plyr->height /2 + -i * cos(map->p_orient), get_rgba(255, 0, 0, 255));
		i++;
	}
}
void	draw_2d_map(mlx_t *mlx, t_map *map, t_images *images)
{
	int			i;
	int			k;
	int			x;
	int			y;
	
	images->black = mlx_load_png("assets/black.png");
	images->white = mlx_load_png("assets/white.png");
	images->player = mlx_load_png("assets/player.png");
images->blk = mlx_texture_to_image(mlx, images->black);
	images->wht = mlx_texture_to_image(mlx, images->white);
	images->plyr = mlx_texture_to_image(mlx, images->player);
	images->dir = mlx_new_image(mlx, 64, 64);
	//mlx_resize_image(images->plyr, 8, 8);
	images->bg = mlx_new_image(mlx, 1366, 768);
	ft_memset(images->bg->pixels, 180, images->bg->width * images->bg->height * BPP);
	mlx_image_to_window(mlx, images->bg, 0, 0);
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
				mlx_image_to_window(mlx, images->blk, (k + 2) * 64, (i + 2) * 64);
			}
			else if (map->map[i][k] == 'N')
			{
				map->p_pos_x = (k + 2) * 64;
				map->p_pos_y = (i + 2) * 64;
				map->p_orient = 0;
				mlx_image_to_window(mlx, images->wht, (k + 2) * 64, (i + 2) * 64);
			}	
			else if (map->map[i][k] == '0')
				mlx_image_to_window(mlx, images->wht, (k + 2) * 64, (i + 2) * 64);
			k++;
		}
		k = 0;
		i++;	
	}
	mlx_image_to_window(mlx, images->plyr, map->p_pos_x, map->p_pos_y);
	draw_direction(mlx, map, images);
}

void	ft_movehook(void *param)
{
	t_map *map;

	map = (t_map *)param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		map->p_pos_y -= 5;
		map->images->plyr->instances[0].y = map->p_pos_y;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
		{
		map->p_pos_y += 5;
		map->images->plyr->instances[0].y = map->p_pos_y;
	}

	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	{
		map->p_pos_x -= 5;
		map->images->plyr->instances[0].x = map->p_pos_x;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	{
		map->p_pos_x += 5;
		map->images->plyr->instances[0].x = map->p_pos_x;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->p_orient -= 1 * DEG_2_RAD;
		if (map->p_orient <= 0)
			map->p_orient += 2 * M_PI;
		printf("Degrees: %f\n", map->p_orient / DEG_2_RAD);
		draw_direction(map->mlx, map, map->images);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->p_orient += 1 * DEG_2_RAD;
		if (map->p_orient >= 2 * M_PI)
			map->p_orient -= 2 * M_PI;
		printf("Degrees: %f\n", map->p_orient / DEG_2_RAD);
		draw_direction(map->mlx, map, map->images);
	}
}

int cub3d_mlx(void)
{
	mlx_t	*mlx;
	t_map 	map;
	t_images images;
	
	map.images = &images;
	map.map = ft_calloc(10, sizeof(char *));
	map.map[0] = ft_strdup("111111111");
	map.map[1] = ft_strdup("100000001");
	map.map[2] = ft_strdup("100000001");
	map.map[3] = ft_strdup("100000001");
	map.map[4] = ft_strdup("1000N0001");
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
	map.mlx = mlx;
	draw_2d_map(mlx, &map, &images);
	mlx_loop_hook(mlx, ft_movehook, &map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_2d(map.map);
	return (EXIT_SUCCESS);
}