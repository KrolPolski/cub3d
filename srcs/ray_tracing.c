/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:27:52 by clundber          #+#    #+#             */
/*   Updated: 2024/05/16 16:11:47 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ray_trace(mlx_t *mlx, t_map *map, t_images *images)
{
	int	pixels;
	int	deg;
	int	ray_size;
	unsigned int	y;
	unsigned int	x;
	bool			pos_wall;
	bool			neg_wall;


	y = 0;
	x = 0;
	ray_size = 500;
	deg = 0;
	mlx_delete_image(mlx, images->fg);
	images->fg = mlx_new_image(mlx, ray_size, ray_size);
	mlx_image_to_window(mlx, images->fg, map->p_pos_x + 32 - (ray_size / 2), map->p_pos_y + 32 - (ray_size / 2));
	while (deg <= 33)
	{
		pixels = 0;
		pos_wall = false;
		neg_wall = false;
		while (pixels < (ray_size / 2))
		{
				y = (map->p_pos_y - 32 - pixels * cos(map->p_orient + deg * DEG_2_RAD)) / 64;
				x = (map->p_pos_x - 32 + pixels * sin(map->p_orient + deg * DEG_2_RAD)) / 64;
			if (pos_wall == false && map->map[y][x] != '1')
				mlx_put_pixel(images->fg, (ray_size / 2) + pixels * sin(map->p_orient + deg * DEG_2_RAD), (ray_size / 2) - pixels * cos(map->p_orient + deg * DEG_2_RAD), get_rgba(255, 0, 0, 255));
			else
				pos_wall = true;

			y = (map->p_pos_y - 32 - pixels * cos(map->p_orient - deg * DEG_2_RAD)) / 64;
			x = (map->p_pos_x - 32 + pixels * sin(map->p_orient - deg * DEG_2_RAD)) / 64;
			if (neg_wall == false && map->map[y][x] != '1')
				mlx_put_pixel(images->fg, (ray_size / 2) + pixels * sin(map->p_orient - deg * DEG_2_RAD), (ray_size / 2) - pixels * cos(map->p_orient - deg * DEG_2_RAD), get_rgba(255, 0, 0, 255));
			else
				neg_wall = true;
			pixels++;
		}
		deg++;
	}
}
