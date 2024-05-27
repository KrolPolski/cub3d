/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:27:52 by clundber          #+#    #+#             */
/*   Updated: 2024/05/27 18:32:58 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_len(t_map *map, long *x_len, long *y_len, double deg)
{
	double	corner;

	corner = (map->p_orient + (deg * DEG_2_RAD));
	if (map->p_orient / DEG_2_RAD + deg == 90 || map->p_orient / DEG_2_RAD + deg == 270)
		(*y_len) = map->rend_dist;
 	else if (corner > 0 && corner / DEG_2_RAD > 90 && corner / DEG_2_RAD < 270)
		(*y_len) = (64 - ((map->ray->ray_y) % 64)) / cos(corner);
	else
		(*y_len) = ((map->ray->ray_y) % 64) / cos(corner);
	if (corner > 0 && corner / DEG_2_RAD > 90)
		corner += (-90 * DEG_2_RAD);
	else
		corner += (270 * DEG_2_RAD);
  	if ((map->p_orient / DEG_2_RAD) + deg == 90 || (map->p_orient / DEG_2_RAD + deg == 270))
		(*x_len) = map->rend_dist;
    else if (corner > 0 && corner / DEG_2_RAD > 90 && corner / DEG_2_RAD < 270)
		(*x_len) = ((map->ray->ray_x) % 64) / cos(corner);
	else
		(*x_len) = (64 - ((map->ray->ray_x) % 64)) / cos(corner);
	if (*y_len < 0)
        (*y_len) *= -1;
  	if (*x_len < 0)
        (*x_len) *= -1;
} 

void	cast_wall(t_map *map, double dist, float deg, enum e_dir dir, int *row)
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
	if (dir == error)
		color = get_rgba(255, 255, 255, 255);
	pixels = 0;
	if (dist >= map->rend_dist)
	{
		(*row)++;
		return ;
	}
	map->ray->dist = dist * cos(deg * DEG_2_RAD);
	if (map->ray->dist <= 0)
		map->ray->dist = 1;
	top_pixel = 0;
	column_height = ((float)64 / (float)map->ray->dist) * map->proj_plane;
	top_pixel = (map->s_height / 2) - column_height / 2;
	if (top_pixel < 0)
		top_pixel = 0;
		while (pixels < column_height && top_pixel + pixels < map->s_height)
		{
			mlx_put_pixel(map->images->world, (*row), top_pixel + pixels, color);
			pixels++;
		}
	(*row)++;
}

//void	wall_control(t_map *map)

void	ray_caster(mlx_t *mlx, t_map *map, t_images *images)
{
	double	deg;
	long	y_len;
	long	x_len;
	int		row;

	row = 0;

	map->ray->ray_x = map->p_pos_x;
	map->ray->ray_y = map->p_pos_y;
	deg = (map->fov_angle / 2) * -1;
	mlx_delete_image(map->mlx, map->images->world);
	map->images->world = mlx_new_image(map->mlx, map->s_width, map->s_height);
	mlx_image_to_window(map->mlx, map->images->world, 0, 0);

	mlx_delete_image(mlx, images->fg);
	images->fg = mlx_new_image(mlx, map->rend_dist * 2, map->rend_dist * 2);
	mlx_image_to_window(mlx, images->fg, map->p_pos_x - map->rend_dist , map->p_pos_y - map->rend_dist);
 	while (deg <= (map->fov_angle / 2) && row < map->s_width)
	{
		y_len = 64;//map->rend_dist;
		x_len = 64;//map->rend_dist;
		get_len(map, &x_len, &y_len, deg);
 		if (map->ray->dist < map->rend_dist)
		{
			if (x_len < y_len)
				map->ray->dist += x_len;
			else
				map->ray->dist += y_len;
		}

/* 	 	while (dist < map->rend_dist && dist <= y_len && dist <= x_len)
		{
			if (map->map_visible)
				mlx_put_pixel(images->fg, map->rend_dist + dist * sin(map->p_orient + deg * DEG_2_RAD), map->rend_dist - dist * cos(map->p_orient + deg * DEG_2_RAD), get_rgba(255, 0, 0, 255));
			dist++;
		} */
		//dist++;
		//printf ("DEG %f dist = %f\n", deg, map->ray->dist);
		map->ray->ray_y = round((map->p_pos_y - (map->ray->dist +1)  * cos(map->p_orient + (deg * DEG_2_RAD))));
		map->ray->ray_x = round((map->p_pos_x + (map->ray->dist +1)  * sin(map->p_orient + (deg * DEG_2_RAD))));
		if (map->ray->ray_y  < 0 || map->ray->ray_x < 0 )
		{
			printf("ray out of bounds detected\n");	
			deg += (double)map->fov_angle / map->s_width;
			map->ray->dist = 0;
		}
		if (map->map[map->ray->ray_y / 64][map->ray->ray_x / 64] == '1' || map->map[map->ray->ray_y / 64][map->ray->ray_x / 64] == '\0' || map->ray->dist > map->rend_dist)
		{
/* 			if (map->ray->ray_y < (map->p_pos_y - 32 - (dist -1)  * cos(map->p_orient + (deg * DEG_2_RAD))))
				cast_wall(map, dist, deg, south, &row);
			else if (map->ray->ray_y > (map->p_pos_y - 32 - (dist -1)  * cos(map->p_orient + (deg * DEG_2_RAD))))
				cast_wall(map, dist, deg, north, &row);
			else if (map->ray->ray_x < (map->p_pos_x - 32 + (dist -1)  * sin(map->p_orient + (deg * DEG_2_RAD))))
				cast_wall(map, dist, deg, east, &row);
			else if (map->ray->ray_x > (map->p_pos_x - 32 + (dist -1)  * sin(map->p_orient + (deg * DEG_2_RAD))))
				cast_wall(map, dist, deg, east, &row); */

 			if (map->ray->ray_y % 64 <= 1)
				cast_wall(map, map->ray->dist, deg, north, &row);
			else if (map->ray->ray_y % 64 == 63)
				cast_wall(map, map->ray->dist, deg, south, &row);
			else if (map->ray->ray_x % 64  <= 1)
				cast_wall(map, map->ray->dist, deg, west, &row);
			else if (map->ray->ray_x % 64 == 63)
				cast_wall(map, map->ray->dist, deg, east, &row);
			else
				cast_wall(map, map->ray->dist, deg, error, &row);
			deg += (double)map->fov_angle / map->s_width;
			map->ray->dist = 0;
		}
		else
		{
			/* if (map->map_visible)
				mlx_put_pixel(images->fg, map->rend_dist +map->ray->dist * sin(map->p_orient + deg * DEG_2_RAD),
					map->rend_dist - map->ray->dist * cos(map->p_orient + deg * DEG_2_RAD),
					get_rgba(255, 0, 0, 255)); */
			map->ray->dist++;
		}
	}
}
