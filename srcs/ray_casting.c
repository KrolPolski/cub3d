/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:27:52 by clundber          #+#    #+#             */
/*   Updated: 2024/05/20 21:36:55 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_len(t_map *map, int *x_len, int *y_len, int deg)
{
	double	corner;

	corner = 0;
		corner = (map->p_orient + (deg * DEG_2_RAD));
 	if (corner / DEG_2_RAD > 90 && corner / DEG_2_RAD < 270)
		(*y_len) = (64 - ((map->p_pos_y +32) % 64)) / cos(corner);
	else
		(*y_len) = ((map->p_pos_y +32) % 64) / cos(corner);
	if (corner / DEG_2_RAD > 90)
		corner += (-90 * DEG_2_RAD);
	else
		corner += (270 * DEG_2_RAD);
     if (corner / DEG_2_RAD > 90 && corner / DEG_2_RAD < 270)
		(*x_len) = ((map->p_pos_x +32) % 64) / cos(corner);
	else
		(*x_len) = (64 - ((map->p_pos_x +32) % 64)) / cos(corner);
 	if (*y_len < 0)
        (*y_len) *= -1;
 	if (*x_len < 0)
        (*x_len) *= -1;
}

void	cast_wall(t_map *map, int dist, int deg)
{
	int	height;
	int	width;
	int	pixels;

	pixels = 0;
	height = (1440 / dist) - ((1440 / dist) /2);
	while (width < 40)
	{
		{
			mlx_put_pixel(map->images->bg, 1250 + width , 600, get_rgba(255, 0, 0, 255));
			width++;
		}	
	}


/* 	while (pixels < 1440 / dist)
	{
		width = 0;
		while (width < 39)
		{
			mlx_put_pixel(map->images->bg, (2560 / 2) + (deg * 38) + width , height - pixels, get_rgba(255, 0, 0, 255));
			width++;
		}
		pixels++;
	} */


}
	//screen size = 2560

void	ray_caster(mlx_t *mlx, t_map *map, t_images *images)
{
	int	pixels;
	int	deg;
	int	ray_size;
	int	y_len;
	int	x_len;
	int	x;
	int	y;
	int	len;

	len = 0;
	pixels = 0;
	x = 0;
	y = 0;
	ray_size = 1024;
	deg = -33;
	mlx_delete_image(mlx, images->fg);
	images->fg = mlx_new_image(mlx, ray_size, ray_size);
	mlx_image_to_window(mlx, images->fg, map->p_pos_x + 32 - (ray_size / 2), map->p_pos_y + 32 - (ray_size / 2));
 	while (deg < 33)
	{
		y_len = INT_MAX;
		x_len = INT_MAX;
		get_len(map, &x_len, &y_len, deg);
  		while (pixels < (ray_size / 2)  && pixels <= y_len && pixels <= x_len)
		{
			mlx_put_pixel(images->fg, (ray_size / 2) + pixels * sin(map->p_orient + deg * DEG_2_RAD), (ray_size / 2) - pixels * cos(map->p_orient + deg * DEG_2_RAD), get_rgba(255, 0, 0, 255));
			pixels++;
		}
		y = (map->p_pos_y - 32 - pixels * cos(map->p_orient + deg * DEG_2_RAD)) / 64;
		x = (map->p_pos_x - 32 + pixels * sin(map->p_orient + deg * DEG_2_RAD)) / 64;
		if (map->map[y][x] == '1' || pixels >= (ray_size / 2))
		{
		//	cast_wall(map, pixels, deg);
			deg++;
			pixels = 0;
		}
		else
		{
			mlx_put_pixel(images->fg, (ray_size / 2) + pixels * sin(map->p_orient + deg * DEG_2_RAD), (ray_size / 2) - pixels * cos(map->p_orient + deg * DEG_2_RAD), get_rgba(255, 0, 0, 255));
			pixels++;
		}
	}
}
