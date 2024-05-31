/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:27:52 by clundber          #+#    #+#             */
/*   Updated: 2024/05/31 12:11:35 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	modulus_64(float pos)
{
	float ret;

	ret = floor(pos / 64) * 64;
	ret = pos - ret;
	return (ret);
}
void	get_x_dist(t_map *map, float deg)
{
	float	angle;
	float	prev_y;
	float	prev_x;
	float	delta_y;
	float  	delta_x;
	float	curr_x;
	float	curr_y;

	angle = (map->p_orient + (deg * DEG_2_RAD));
	if (angle * DEG_2_RAD == 0)
		angle += 0.01;
 	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle * DEG_2_RAD == 0 ||  angle * DEG_2_RAD == 180)
	{
		map->ray->x_dist = map->rend_dist + 10;
		return ;
	}
	//printf("This is X function\n");
 	if (angle / DEG_2_RAD > 0 && angle / DEG_2_RAD < 180)
	{
		//prev_x = map->ray->ray_x - (modulus_64(map->ray->ray_x) + 64);
		prev_x = floor(map->ray->ray_x  / 64) * 64 + 64;
		delta_x = 64;
	}
	else 
	{
		//prev_x = map->ray->ray_x - (modulus_64(map->ray->ray_x) - 1);
		prev_x = floor(map->ray->ray_x  / 64) * 64 - 1;
		delta_x = -64;
	}

	prev_y = floor(map->ray->ray_y + (map->ray->ray_x - prev_x) / tan(angle));
	delta_y = (float)64 / tan(angle);
	//printf("prev_y = %d prev_x = %d\n", (int)prev_y / 64, (int)prev_x / 64);
	//printf("X prev_y = %f prev_x = %f\n", prev_y, prev_x);
	if ((int)prev_y / 64 < 0 || (int)prev_y / 64 > map->map_y_border || (int)prev_x / 64 < 0 || (int)prev_x / 64 > map->map_x_border)
	{
		map->ray->x_dist = map->rend_dist + 10;
		return ;
	}
	if (map->map[(int)prev_y / 64][(int)prev_x / 64] != '1')
	{
	//printf("mamma mia\n");
		while (true)
		{
			curr_x = (prev_x + delta_x);
			curr_y = (prev_y + delta_y);
			if ((int)curr_y / 64 < 0 || (int)curr_y / 64 > map->map_y_border || (int)curr_x / 64 < 0 || (int)curr_x / 64 > map->map_x_border)
			{
				map->ray->x_dist = map->rend_dist + 10;
				return ;
			}
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
	map->ray->x_dist = sqrt(pow((float)map->p_pos_x - curr_x, 2) + pow((float)map->p_pos_y - curr_y, 2));
	//map->ray->x_dist = fabs((map->p_pos_x - curr_x) / cos(angle));
}

void	get_y_dist(t_map *map, float deg)
{
	float	angle;
	float	prev_y;
	float	prev_x;
	float	delta_y;
	float  delta_x;
	float	curr_x;
	float	curr_y;

	angle = (map->p_orient + (deg * DEG_2_RAD));
	if (angle * DEG_2_RAD == 0)
		angle += 0.01;
	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	if (angle * DEG_2_RAD == 90 ||  angle * DEG_2_RAD == 270)
	{
		map->ray->y_dist = map->rend_dist + 10;
		return ;
	}
	//printf("This is Y function\n");
//	printf("angle = %f\n", angle / DEG_2_RAD);
 	if (angle / DEG_2_RAD < 270 && angle / DEG_2_RAD > 180)
	{
		//prev_y = map->ray->ray_y - (modulus_64(map->ray->ray_y) + 64);
		prev_y = floor(map->ray->ray_y / 64) * 64 + 64;
		delta_y = 64;
	}
	else
	{
		//prev_y = map->ray->ray_y - (modulus_64(map->ray->ray_y) - 1);
		prev_y = floor(map->ray->ray_y / 64) * 64 - 1;
		delta_y = -64;
	}
	prev_x = floor(map->ray->ray_y + (map->ray->ray_y - prev_y) / tan (angle));
	delta_x = (float)64 / tan(angle);
	printf("prev_y = %d prev_x = %d\n", (int)prev_y / 64, (int)prev_x / 64);
	if ((int)prev_y / 64 < 0 || (int)prev_y / 64 > map->map_y_border || (int)prev_x / 64 < 0 || (int)prev_x / 64 > map->map_x_border)
	{
		map->ray->y_dist = map->rend_dist + 10;
		return ;
	}
	if (map->map[(int)prev_y / 64][(int)prev_x / 64] != '1')
	{
		while (true)
		{
			printf("prev_x = %d and x border = %d\n", (int)prev_x / 64, map->map_x_border);
			printf("prev_y = %d and y border = %d\n", (int)prev_y / 64, map->map_y_border);	
			curr_x = (prev_x + delta_x);
			curr_y = (prev_y + delta_y);
			printf("curr_x = %d and x border = %d\n", (int)curr_x / 64, map->map_x_border);
			printf("curr_y = %d and y border = %d\n", (int)curr_y / 64, map->map_y_border);	
			if ((int)curr_y / 64 < 0 || (int)curr_y / 64 > map->map_y_border || (int)curr_x / 64 < 0 || (int)curr_x / 64 > map->map_x_border)
			{
							
				printf("exited here\n");
				map->ray->y_dist = map->rend_dist + 10;
				return ;
			}
			if (map->map[(int)curr_y / 64][(int)curr_x / 64] == '1')
				break ;
			else
			{
			prev_x = curr_x;
			prev_y = curr_y;
			//printf("prev_y = %d prev_x = %d\n", (int)prev_y / 64, (int)prev_x / 64);
			}
		}
	}
	else
	{
		curr_x = prev_x;
		curr_y = prev_y;
	}
	//printf("curr_y = %d curr_x = %d\n", (int)curr_y / 64, (int)curr_x / 64);
	map->ray->y_dist = sqrt(pow((float)map->p_pos_x - curr_x, 2) + pow((float)map->p_pos_y - curr_y, 2));
	//map->ray->y_dist = fabs((map->p_pos_y - curr_y) / cos(angle));
}

void	cast_wall(t_map *map, float dist, float deg, enum e_dir dir, int *row)
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
	column_height = ((float)64 / map->ray->dist) * (float)map->proj_plane;
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
	float	deg;
	float	y_len;
	float	x_len;
	int		row;

	row = 0;

	map->ray->ray_x = (float)map->p_pos_x;
	map->ray->ray_y = (float)map->p_pos_y;
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
		//printf("got here!\n");
		get_y_dist(map, deg);
		//printf("got here2!\n");
		//map->ray->x_dist = 500;
		get_x_dist(map, deg);


		//printf("got here3!\n");

	if (map->ray->x_dist < map->ray->y_dist)
		map->ray->dist = map->ray->x_dist;
	else
		map->ray->dist = map->ray->y_dist;
	printf("\n");
	printf("y_dist = %f\n", map->ray->y_dist);
	printf("x_dist = %f\n", map->ray->x_dist);	
	printf("DIST = %f\n", map->ray->dist);
	printf("ray angle is %f\n", map->p_orient / DEG_2_RAD + deg);
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
		//	printf("DEG = %f\n", deg);

			cast_wall(map, map->ray->dist, deg, error, &row);
			deg += (float)(map->fov_angle / map->s_width);
			map->ray->dist = 0;

		}

}
