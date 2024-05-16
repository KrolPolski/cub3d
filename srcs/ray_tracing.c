/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:27:52 by clundber          #+#    #+#             */
/*   Updated: 2024/05/16 14:50:21 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ray_trace(mlx_t *mlx, t_map *map, t_images *images)
{
	int	pixels;
	int	deg;

	deg = 0;
	mlx_delete_image(mlx, images->fg);
	//images->fg = mlx_new_image(mlx, 2560, 1440);
	images->fg = mlx_new_image(mlx, 600, 600);
	mlx_image_to_window(mlx, images->fg, map->p_pos_x + 32 - 300, map->p_pos_y + 32 - 300);
	//printf("x = %d, y = %d\n", map->p_pos_x, map->p_pos_y);
	while (deg <= 66)
	{
		pixels = 0;
		while (pixels < 300)
		{
			//mlx_put_pixel(images->fg,  map->p_pos_x + pixels + map->x_offset * sin(map->p_orient), map->p_pos_y + map->y_offset + pixels * cos(map->p_orient), get_rgba(255, 0, 0, 255));	
		//	mlx_put_pixel(images->fg, 300 + pixels * sin(map->p_orient), 300 - pixels * cos(map->p_orient), get_rgba(255, 0, 0, 255));
			mlx_put_pixel(images->fg, 300 + pixels * sin(map->p_orient + deg * DEG_2_RAD), 300 - pixels * cos(map->p_orient + deg * DEG_2_RAD), get_rgba(255, 0, 0, 255));
			mlx_put_pixel(images->fg, 300 + pixels * sin(map->p_orient - deg * DEG_2_RAD), 300 - pixels * cos(map->p_orient - deg * DEG_2_RAD), get_rgba(255, 0, 0, 255));

		//	mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient + 30 * DEG_2_RAD), images->plyr->height /2 - i * cos(map->p_orient + 30 * DEG_2_RAD), get_rgba(255, 0, 255, 255));
		//	mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient - 30 * DEG_2_RAD), images->plyr->height /2 - i * cos(map->p_orient - 30 * DEG_2_RAD), get_rgba(255, 0, 255, 255));
			pixels++;
		}
		deg++;
	}
}
