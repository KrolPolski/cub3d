/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:27:52 by clundber          #+#    #+#             */
/*   Updated: 2024/05/20 18:25:16 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_len(t_map *map, int *x_len, int *y_len, int deg)
{
	double	corner;

	corner = 0;
		corner = (map->p_orient + (deg * DEG_2_RAD));
 	if (corner / DEG_2_RAD > 90 && corner / DEG_2_RAD < 270)
		(*y_len) = (32 - ((map->p_pos_y +16) % 32)) / cos(corner);
	else
		(*y_len) = ((map->p_pos_y +16) % 32) / cos(corner);
	if (corner / DEG_2_RAD > 90)
		corner += (-90 * DEG_2_RAD);
	else
		corner += (270 * DEG_2_RAD);
     if (corner / DEG_2_RAD > 90 && corner / DEG_2_RAD < 270)
		(*x_len) = ((map->p_pos_x +16) % 32) / cos(corner);
	else
		(*x_len) = (32 - ((map->p_pos_x +16) % 32)) / cos(corner);
 	if (*y_len < 0)
        (*y_len) *= -1;
 	if (*x_len < 0)
        (*x_len) *= -1;
}

void	ray_caster(mlx_t *mlx, t_map *map, t_images *images)
{
	int	pixels;
	int	deg;
	int	ray_size;
	int	y_len;
	int	x_len;
	int	x;
	int	y;

	pixels = 0;
	x = 0;
	y = 0;
	ray_size = 1024;
	deg = -33;
	mlx_delete_image(mlx, images->fg);
	images->fg = mlx_new_image(mlx, ray_size, ray_size);
	mlx_image_to_window(mlx, images->fg, map->p_pos_x + 16 - (ray_size / 2), map->p_pos_y + 16 - (ray_size / 2));
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
		y = (map->p_pos_y - 16 - pixels * cos(map->p_orient + deg * DEG_2_RAD)) / 32;
		x = (map->p_pos_x - 16 + pixels * sin(map->p_orient + deg * DEG_2_RAD)) / 32;
		if (map->map[y][x] == '1' || pixels >= (ray_size / 2))
		{
			deg++;
			//paint the row
			pixels = 0;
		}
		else
		{
			mlx_put_pixel(images->fg, (ray_size / 2) + pixels * sin(map->p_orient + deg * DEG_2_RAD), (ray_size / 2) - pixels * cos(map->p_orient + deg * DEG_2_RAD), get_rgba(255, 0, 0, 255));
			pixels++;
		}
	}
}