/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:27:52 by clundber          #+#    #+#             */
/*   Updated: 2024/06/20 12:55:25 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ray_caster(mlx_t *mlx, t_map *map, t_images *images)
{
	int x;
	int w;
	t_ray ray;
	map->p_dir_x = -1;
	map->p_dir_y = 0;
	map->plane_x = 0;
	map->plane_y = 0.66;

	x = 0;
	w = map->s_width;
	
	while(x < w)
    {
      //calculate ray position and direction
      map->camera_x = 2 * x / (double)(w) - 1; //x-coordinate in camera space
      ray.ray_x = map->p_dir_x + map->plane_x * map->camera_x;
	  ray.ray_y = map->p_dir_y + map->plane_y * map->camera_x;
	  w++;
	}
}
