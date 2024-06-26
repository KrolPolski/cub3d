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

void	ray_caster(mlx_t *mlx, t_map *map, t_images *images, t_vector *vec)
{
	int x;
	int w;
	t_ray ray;
	int map_x;
	int map_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	double perp_wall_dist;
	int step_x;
	int step_y;
	int hit;
	int side;


	x = 0;
	w = map->s_width;
	
	while(x < w)
    {
      //calculate ray position and direction
    	vec->camera_x = 2 * x / (double)(w) - 1; //x-coordinate in camera space
    	ray.ray_dir_x = vec->p_dir_x + vec->plane_x * vec->camera_x;
		ray.ray_dir_y = vec->p_dir_y + vec->plane_y * vec->camera_x;
		map_x = (int)vec->p_pos_x;
		map_y = (int)vec->p_pos_y;
		if (ray.ray_dir_x != 0)
			delta_dist_x = abs(1 / ray.ray_dir_x);
		else
			delta_dist_x = 1e30;
		if (ray.ray_dir_y != 0)
			delta_dist_y = abs(1 / ray.ray_dir_y);
		else
			delta_dist_y = 1e30;
		hit = 0;
		if (ray.ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (vec->p_pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - vec->p_pos_x) * delta_dist_x;
		}
		if (ray.ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (vec->p_pos_y - map_y) * delta_dist_y;
		}
		else 
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - vec->p_pos_y) * delta_dist_y;
		}
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
		}
	  x++;
	}
}
