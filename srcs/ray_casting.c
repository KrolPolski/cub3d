/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:27:52 by clundber          #+#    #+#             */
/*   Updated: 2024/05/22 22:07:26 by clundber         ###   ########.fr       */
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
	int	top_pixel;
	int	pixels;
	int	color;
	float	angle;
	unsigned int column_height;

	angle = 0;
	if (dir == north)
		color = get_rgba(100, 100, 200, 255);
	if (dir == east)
		color = get_rgba(100, 0, 0, 255);
	if (dir == south)
		color = get_rgba(0, 0, 200, 255);
	if (dir == west)
		color = get_rgba(100, 100, 0, 255);
	pixels = 0;
 	if (deg < 0)
		angle = ((deg * -1) + 90) * DEG_2_RAD;
	else
		angle = (deg + 90) * DEG_2_RAD;
	dist = dist * sin(angle);
	if (dist >= map->rend_dist)
	{
		(*row)++;
		return;
	}
	if (dist <= 0)
		dist = 1;
	top_pixel = 0;
	column_height = ((float)64 / (float)dist) * map->proj_plane;
	top_pixel = (map->s_height / 2) - column_height / 2;
	if (top_pixel < 0)// && height > map->s_height)
		top_pixel = 0;
		while (pixels < column_height && top_pixel + pixels < map->s_height)
		{
			mlx_put_pixel(map->images->world, (*row), top_pixel + pixels, color);
			pixels++;
		}
	(*row)++;
}

void	ray_caster(mlx_t *mlx, t_map *map, t_images *images)
{
	int	dist;
	double	deg;
	int	y_len;
	int	x_len;
	int	x;
	int	y;
	int	row;

	row = 0;
	dist = 0;
	x = 0;
	y = 0;
	deg = (map->fov_angle / 2) * -1;
	mlx_delete_image(map->mlx, map->images->world);
	map->images->world = mlx_new_image(map->mlx, map->s_width, map->s_height);
	mlx_image_to_window(map->mlx, map->images->world, 0, 0);

	mlx_delete_image(mlx, images->fg);
	images->fg = mlx_new_image(mlx, map->rend_dist * 2, map->rend_dist * 2);
	mlx_image_to_window(mlx, images->fg, map->p_pos_x + 32 - map->rend_dist , map->p_pos_y + 32 - map->rend_dist);
 	while (deg <= (map->fov_angle / 2) && row < map->s_width)
	{
		y_len = map->rend_dist;
		x_len = map->rend_dist;
		get_len(map, &x_len, &y_len, deg);
  		while (dist < map->rend_dist && dist <= y_len && dist <= x_len)
		{
			if (map->map_visible)
				mlx_put_pixel(images->fg, map->rend_dist + dist * sin(map->p_orient + deg * DEG_2_RAD), map->rend_dist - dist * cos(map->p_orient + deg * DEG_2_RAD), get_rgba(255, 0, 0, 255));
			dist++;
		}
		y = (map->p_pos_y - 32 - dist  * cos(map->p_orient + (deg * DEG_2_RAD)));
		x = (map->p_pos_x - 32 + dist  * sin(map->p_orient + (deg * DEG_2_RAD)));
		if (map->map[y / 64][x / 64] == '1' )//|| dist >= map->rend_dist)
		{
			if (y % 64 == 0)
				cast_wall(map, dist, deg, north, &row);
			else if (x % 64  == 0)
				cast_wall(map, dist, deg, west, &row);
			else if (y % 64 == 63)
				cast_wall(map, dist, deg, south, &row);
			else
				cast_wall(map, dist, deg, east, &row);
			deg += (double)60 / map->s_width;
			dist = 0;
		}
		else
		{
			if (map->map_visible)
				mlx_put_pixel(images->fg, map->rend_dist + dist * sin(map->p_orient + deg * DEG_2_RAD), map->rend_dist - dist * cos(map->p_orient + deg * DEG_2_RAD), get_rgba(255, 0, 0, 255));
			dist++;
		}
	}
}
