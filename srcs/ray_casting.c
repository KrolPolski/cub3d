/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:27:52 by clundber          #+#    #+#             */
/*   Updated: 2024/05/16 16:17:10 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_abs(t_map *map, int *x_abs, int *y_abs, int deg)
{
	if (map->p_orient / DEG_2_RAD > 270  || map->p_orient / DEG_2_RAD < 90)
		(*y_abs) = (64 - (map->p_pos_y % 64)) / cos(map->p_orient + deg * DEG_2_RAD);
	else if (map->p_orient / DEG_2_RAD == 270  || map->p_orient / DEG_2_RAD == 90)
		(*y_abs) = 5 * 64;
	else
		(*y_abs) = (64 - map->p_pos_y % 64) / cos((map->p_orient + (180 * DEG_2_RAD))  + deg * DEG_2_RAD);
	if (map->p_orient / DEG_2_RAD >= 0  && map->p_orient / DEG_2_RAD <= 180)
		(*x_abs) = 64 / sin(map->p_orient + deg * DEG_2_RAD);
	else if (map->p_orient / DEG_2_RAD == 0  || map->p_orient / DEG_2_RAD == 180)
		(*x_abs) = 5* 64;
	else
		(*x_abs) = 64 / sin((map->p_orient + (-180 * DEG_2_RAD))  + deg * DEG_2_RAD);			

}

void	ray_caster(mlx_t *mlx, t_map *map, t_images *images)
{
	int	pixels;
	int	deg;
	int	ray_size;
	unsigned int	y;
	unsigned int	x;
	bool			pos_wall;
	bool			neg_wall;
	int				abs;
	int				x_abs;
	bool			neg_deg;

	neg_deg = false;
	abs = INT_MAX;
	x_abs = INT_MAX;
	y = 0;
	x = 0;
	ray_size = 500;
	deg = 0;
	mlx_delete_image(mlx, images->fg);
	images->fg = mlx_new_image(mlx, ray_size, ray_size);
	mlx_image_to_window(mlx, images->fg, map->p_pos_x + 32 - (ray_size / 2), map->p_pos_y + 32 - (ray_size / 2));
	
	while (deg < 33)
	{
		pixels = 0;
		pos_wall = false;
		neg_wall = false;
		get_abs(map, &x_abs, &abs, deg);
		while (pixels < (ray_size / 2) && pixels < abs)// && pixels < x_abs)//pos_wall == false && neg_wall == false)
		{
			mlx_put_pixel(images->fg, (ray_size / 2) + pixels * sin(map->p_orient + deg * DEG_2_RAD), (ray_size / 2) - pixels * cos(map->p_orient + deg * DEG_2_RAD), get_rgba(255, 0, 0, 255));
			pixels++;
			y = (map->p_pos_y - 32 - pixels * cos(map->p_orient + deg * DEG_2_RAD));
			x = (map->p_pos_x - 32 + pixels * sin(map->p_orient + deg * DEG_2_RAD));
			if (y % 64 == 0)
				pos_wall = true;
			if (x % 64 == 0)
				neg_wall = true;
		}
/* 		if (pos_wall == true)
		{
			if (map->p_orient / DEG_2_RAD > 270  || map->p_orient / DEG_2_RAD < 90)
				abs = 64 / cos(map->p_orient + deg * DEG_2_RAD) + pixels;
			else if (map->p_orient / DEG_2_RAD == 270  || map->p_orient / DEG_2_RAD == 90)
				abs = ray_size / 2;
			else
				abs = 64 / cos((map->p_orient + (180 * DEG_2_RAD))  + deg * DEG_2_RAD) + pixels;
		}
		else
			if (map->p_orient / DEG_2_RAD >= 0  && map->p_orient / DEG_2_RAD <= 180)
				x_abs = 64 / sin(map->p_orient + deg * DEG_2_RAD) + pixels;
			else if (map->p_orient / DEG_2_RAD == 0  || map->p_orient / DEG_2_RAD == 180)
				x_abs = ray_size /2;
			else
				x_abs = 64 / sin((map->p_orient + (-180 * DEG_2_RAD))  + deg * DEG_2_RAD) + pixels;			 */
/*  		while (pixels < (ray_size / 2)  && pixels <= abs && pixels <= x_abs)
		{
			mlx_put_pixel(images->fg, (ray_size / 2) + pixels * sin(map->p_orient + deg * DEG_2_RAD), (ray_size / 2) - pixels * cos(map->p_orient + deg * DEG_2_RAD), get_rgba(255, 0, 0, 255));
			pixels++;
		} */
		deg++;

	}
	
/* 	while (deg <= 33)
	{

		pixels = 0;
		pos_wall = false;
		neg_wall = false;
		while (pixels < (ray_size / 2))
		{
				y = (map->p_pos_y - 32 - pixels * cos(map->p_orient + deg * DEG_2_RAD)) / 64;
				x = (map->p_pos_x - 32 + pixels * sin(map->p_orient + deg * DEG_2_RAD)) / 64;
			abs = 64 / cos(map->p_orient + deg * DEG_2_RAD);
			printf ("abs = %d\n", abs);
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
	} */
}

/*  deltaDistX = abs(|rayDir| / rayDirX)
deltaDistY = abs(|rayDir| / rayDirY)

Where |rayDir| is the length of the vector rayDirX, rayDirY (that is sqrt(rayDirX * rayDirX + rayDirY * rayDirY)): 
you can indeed verify that e.g. sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX)) equals abs(sqrt(rayDirX * rayDirX + rayDirY * rayDirY) / rayDirX). 
However, we can use 1 instead of |rayDir|, because only the *ratio* between deltaDistX and deltaDistY matters for the DDA code that follows later below, so we get:

deltaDistX = abs(1 / rayDirX)
deltaDistY = abs(1 / rayDirY)

Due to this, the deltaDist and sideDist values used in the code do not match the lengths shown in the 
picture above, but their relative sizes all still match.  */
