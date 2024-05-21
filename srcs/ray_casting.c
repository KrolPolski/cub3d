/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:27:52 by clundber          #+#    #+#             */
/*   Updated: 2024/05/21 19:56:30 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_len(t_map *map, int *x_len, int *y_len, int deg)
{
	double	corner;

	corner = 0;
		corner = (map->p_orient + (deg * DEG_2_RAD));
 	if (corner > 0 && corner / DEG_2_RAD > 90 && corner / DEG_2_RAD < 270)
		(*y_len) = (64 - ((map->p_pos_y +32) % 64)) / cos(corner);
	else
		(*y_len) = ((map->p_pos_y +32) % 64) / cos(corner);
	if (corner > 0 && corner / DEG_2_RAD > 90)
		corner += (-90 * DEG_2_RAD);
	else
		corner += (270 * DEG_2_RAD);
     if (corner > 0 && corner / DEG_2_RAD > 90 && corner / DEG_2_RAD < 270)
		(*x_len) = ((map->p_pos_x +32) % 64) / cos(corner);
	else
		(*x_len) = (64 - ((map->p_pos_x +32) % 64)) / cos(corner);
 	if (*y_len < 0)
        (*y_len) *= -1;
 	if (*x_len < 0)
        (*x_len) *= -1;
}

void	cast_wall(t_map *map, int dist, float deg, enum e_dir dir, int *row)
{
	int	height;
	int	pixels;
	int	color;
	float	angle;

	angle = 0;
	if (dir == north)
		color = get_rgba(100, 100, 200, 255);
	if (dir == east)
		color = get_rgba(100, 0, 0, 255);
	if (dir == south)
		color = get_rgba(0, 0, 200, 255);
	if (dir == west)
		color = get_rgba(100, 100, 0, 255);
	//printf("here I am\n");
	pixels = 0;
 	if (deg < 0)
		angle = ((deg * -1) + 90) * DEG_2_RAD;
	else
		angle = (deg + 90) * DEG_2_RAD;
	dist = dist * sin(angle);
     	if (dist > 10)
		dist /= 10;
	else if (dist == 0)
		dist = 1;
	height = (map->s_height / 2) - ((map->s_height / dist * map->proj_plane) /2);
	//height = 64 / dist * 277;
/*   	while (width < 7)
	{
		pixels = 0; */
		while (pixels < (64 / dist * map->proj_plane))//map->s_height / dist)// && (height + pixels) < 1440 && (height + pixels) > 0)
		{
			mlx_put_pixel(map->images->world, (*row), height + pixels, color);//get_rgba(100, 100, 200, 255));
			pixels++;
		}
	(*row)++;
/* 	width++;
	} */
}
	//screen size = 2560

void	ray_caster(mlx_t *mlx, t_map *map, t_images *images)
{
	int	pixels;
	double	deg;
	int	ray_size;
	int	y_len;
	int	x_len;
	int	x;
	int	y;
	int	len;
	int	row;

	row = 0;
	len = 0;
	pixels = 0;
	x = 0;
	y = 0;
	ray_size = 1024;
	deg = -30;

	mlx_delete_image(map->mlx, map->images->world);
	map->images->world = mlx_new_image(map->mlx, map->s_width, map->s_height);
	mlx_image_to_window(map->mlx, map->images->world, 0, 0);

	//mlx_delete_image(mlx, images->fg);
	//images->fg = mlx_new_image(mlx, ray_size, ray_size);
	//mlx_image_to_window(mlx, images->fg, map->p_pos_x + 32 - (ray_size / 2), map->p_pos_y + 32 - (ray_size / 2));
 	while (deg <= 30)
	{
		y_len = INT_MAX;
		x_len = INT_MAX;
		get_len(map, &x_len, &y_len, deg);
  		while (pixels < (ray_size / 2)  && pixels <= y_len && pixels <= x_len)
		{
		//	mlx_put_pixel(images->fg, (ray_size / 2) + pixels * sin(map->p_orient + (deg * DEG_2_RAD)), (ray_size / 2) - pixels * cos(map->p_orient + (deg * DEG_2_RAD)), get_rgba(255, 0, 0, 255));
			pixels++;
		}
		y = (map->p_pos_y - 32 - pixels  * cos(map->p_orient + (deg * DEG_2_RAD)));// / 64;
		x = (map->p_pos_x - 32 + pixels  * sin(map->p_orient + (deg * DEG_2_RAD)));// / 64;
		if (map->map[y / 64][x / 64] == '1' || pixels >= (ray_size / 2))
		{
			if (y % 64 <= 1)
				cast_wall(map, pixels, deg, north, &row);
			else if (y % 64 > 62)
				cast_wall(map, pixels, deg, south, &row);
			else if (x % 64  < 1)
				cast_wall(map, pixels, deg, west, &row);
			else
				cast_wall(map, pixels, deg, east, &row);
			//deg += 0.2;
			deg += (double)60 / map->s_width;
		//	printf("width = %d\n", map->s_width);
		//	printf("deg = %f\n", deg);
			pixels = 0;
		}
		else
		{
		//	mlx_put_pixel(images->fg, (ray_size / 2) + pixels * sin(map->p_orient + (deg * DEG_2_RAD)), (ray_size / 2) - pixels * cos(map->p_orient + (deg * DEG_2_RAD)), get_rgba(255, 0, 0, 255));
			pixels++;
		}
	}
}
