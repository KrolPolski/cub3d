/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:27:52 by clundber          #+#    #+#             */
/*   Updated: 2024/05/22 10:02:56 by rboudwin         ###   ########.fr       */
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
	mlx_image_to_window(mlx, images->fg, map->p_pos_x + 32 - (ray_size / 2), map->p_pos_y + 32 - (ray_size / 2));
 	while (deg < 33)
	{
		y_len = INT_MAX;
		x_len = INT_MAX;
		get_len(map, &x_len, &y_len, deg);
  		while (pixels < (ray_size / 2)  && pixels <= y_len && pixels <= x_len)
		{
			if (map->map_visible)
				mlx_put_pixel(images->fg, (ray_size / 2) + pixels * sin(map->p_orient + deg * DEG_2_RAD), (ray_size / 2) - pixels * cos(map->p_orient + deg * DEG_2_RAD), get_rgba(255, 0, 0, 255));
			pixels++;
		}
		y = (map->p_pos_y - 32 - pixels * cos(map->p_orient + deg * DEG_2_RAD)) / 64;
		x = (map->p_pos_x - 32 + pixels * sin(map->p_orient + deg * DEG_2_RAD)) / 64;
		if (map->map[y][x] == '1' || pixels >= (ray_size / 2))
		{
			deg++;
			//paint the row
			pixels = 0;
		}
		else
		{
			if (map->map_visible)
				mlx_put_pixel(images->fg, (ray_size / 2) + pixels * sin(map->p_orient + deg * DEG_2_RAD), (ray_size / 2) - pixels * cos(map->p_orient + deg * DEG_2_RAD), get_rgba(255, 0, 0, 255));
			pixels++;
		}
	}
}

void	ray_caster2(mlx_t *mlx, t_map *map, t_images *images)
{
	int				pixels;
	int				deg;
	int				ray_size;
	unsigned int	y;
	unsigned int	x;
	bool			pos_wall;
	bool			neg_wall;

	y = 0;
	x = 0;
	ray_size = 1024;
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

	//printf ("math = %d\n", ((map->p_pos_y + 32) % 64));
/*  		while (pixels < (ray_size / 2)&& pos_wall == false && neg_wall == false)// pixels < abs && pixels < x_abs && pos_wall == false && neg_wall == false)
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
  		if (pos_wall == true)
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
				x_abs = 64 / sin((map->p_orient + (-180 * DEG_2_RAD))  + deg * DEG_2_RAD) + pixels; */

/*  deltaDistX = abs(|rayDir| / rayDirX)
deltaDistY = abs(|rayDir| / rayDirY)

Where |rayDir| is the length of the vector rayDirX, rayDirY (that is sqrt(rayDirX * rayDirX + rayDirY * rayDirY)): 
you can indeed verify that e.g. sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX)) equals abs(sqrt(rayDirX * rayDirX + rayDirY * rayDirY) / rayDirX). 
However, we can use 1 instead of |rayDir|, because only the *ratio* between deltaDistX and deltaDistY matters for the DDA code that follows later below, so we get:

deltaDistX = abs(1 / rayDirX)
deltaDistY = abs(1 / rayDirY)

Due to this, the deltaDist and sideDist values used in the code do not match the lengths shown in the 
picture above, but their relative sizes all still match.  */
