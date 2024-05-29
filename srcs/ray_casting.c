/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:27:52 by clundber          #+#    #+#             */
/*   Updated: 2024/05/29 11:47:34 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	modulus_64(double pos)
{
	double ret;

	ret = floor(pos / 64) * 64;
	ret = pos - ret;
	return (ret);
}
void	get_x_dist(t_map *map, double deg)
{
	double	angle;
	double	prev_y;
	double	prev_x;
	double	delta_y;
	double  delta_x;
	double	curr_x;
	double	curr_y;

	angle = (map->p_orient + (deg * DEG_2_RAD));
 	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	printf("Our angle is %f and our ray_x position is %f and our ray_y position is %f\n", angle / DEG_2_RAD, map->ray->ray_x, map->ray->ray_y);
 	if (angle / DEG_2_RAD > 0 && angle / DEG_2_RAD < 180)
	{
		prev_x = (modulus_64(map->ray->ray_x) + 64);
		delta_x = 64;
	}
	else
	{
		prev_x = (modulus_64(map->ray->ray_x) - 1);
		delta_x = -64;
	}

	prev_y = map->ray->ray_y + (prev_x) * tan(angle);
	delta_y = 64 * tan(angle);

	printf("prev_y = %f prev_x = %f\n", prev_y, prev_x);
	if (map->map[(int)prev_y / 64][(int)prev_x / 64] != '1')
	{
	printf("mamma mia\n");
		while (true)
		{
			curr_x = (prev_x + delta_x);
			curr_y = (prev_y + delta_y);
			
			if (map->map[(int)curr_y / 64][(int)curr_x / 64] == '1')
				break ;
			else
			{
			prev_x = curr_x;
			prev_y = curr_y;
			}
		}
	}
	else
	{
		curr_x = prev_x;
		curr_y = prev_y;
	}
	map->ray->x_dist = fabs((map->p_pos_x - curr_x) / cos(angle));
}

void	get_y_dist(t_map *map, double deg)
{
	double	angle;
	double	prev_y;
	double	prev_x;
	double	delta_y;
	double  delta_x;
	double	curr_x;
	double	curr_y;

	angle = (map->p_orient + (deg * DEG_2_RAD));
	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
 	
	if (angle / DEG_2_RAD > 90 && angle / DEG_2_RAD < 270)
	{
		prev_y = (modulus_64(map->ray->ray_y) + 64);
		delta_y = 64;
	}
	else
	{
		prev_y = (modulus_64(map->ray->ray_y) - 1);
		delta_y = -64;
	}
	prev_x = map->ray->ray_x + (delta_y) / tan (angle);
	delta_x = 64 / tan(angle);
	printf("prev_y = %f prev_x = %f\n", prev_y, prev_x);
	if (map->map[(int)prev_y / 64][(int)prev_x / 64] != '1')
	{
		while (true)
		{
			curr_x = (prev_x + delta_x);
			curr_y = (prev_y + delta_y);
			if (map->map[(int)curr_y / 64][(int)curr_x / 64] == '1')
				break ;
			else
			{
			prev_x = curr_x;
			prev_y = curr_y;
			}
		}
	}
	else
	{
		curr_x = prev_x;
		curr_y = prev_y;
	}
	map->ray->y_dist = fabs((map->p_pos_y - curr_y) / cos(angle));
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
	column_height = ((float)64 / map->ray->dist) * (double)map->proj_plane;
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
	double	y_len;
	double	x_len;
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
		printf("got here!\n");
		get_x_dist(map, deg);
		printf("got here2!\n");
		get_y_dist(map, deg);
		printf("got here3!\n");

		if (map->ray->x_dist < map->ray->ray_y)
			map->ray->dist = map->ray->x_dist;
		else
			map->ray->dist = map->ray->y_dist;
/*   //			if (map->ray->ray_y % 64 < 1)
			if(map->ray->ray_y - (64 *(floor(map->ray->ray_y / 64))) < 1)
				cast_wall(map, map->ray->dist, deg, north, &row);
	//		else if (map->ray->ray_y % 64 == 63)
			if(map->ray->ray_y - (64 *(floor(map->ray->ray_y / 64))) >= 63)
				cast_wall(map, map->ray->dist, deg, south, &row);
	//		else if (map->ray->ray_x % 64  < 1)
			if(map->ray->ray_x - (64 *(floor(map->ray->ray_x / 64))) < 1)
				cast_wall(map, map->ray->dist, deg, west, &row);
	//		else if (map->ray->ray_x % 64 == 63)
			if(map->ray->ray_x - (64 *(floor(map->ray->ray_x / 64))) >= 63)
				cast_wall(map, map->ray->dist, deg, east, &row);
			else  */
			
			cast_wall(map, map->ray->dist, deg, error, &row);
			deg += (double)(map->fov_angle / map->s_width);
			map->ray->dist = 0;
		}

}
