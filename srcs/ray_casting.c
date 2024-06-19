/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:27:52 by clundber          #+#    #+#             */
/*   Updated: 2024/06/19 15:43:47 by clundber         ###   ########.fr       */
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
/* void	get_x_dist(t_map *map, float deg)
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
	if (angle / DEG_2_RAD == 0 ||  angle / DEG_2_RAD == 180)
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
	//tested that the first gridline is working correctly.
	prev_y = floor(map->ray->ray_y + (map->ray->ray_x - prev_x) / tan(angle));
	//delta_y = delta_x * tan(angle);
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
	float  	delta_x;
	float	curr_x;
	float	curr_y;

	angle = (map->p_orient + (deg * DEG_2_RAD));
	if (angle * DEG_2_RAD == 0)
		angle += 0.01 * DEG_2_RAD;
 	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle > 2 * M_PI)
		angle -= 2 * M_PI; 

	if (angle / DEG_2_RAD == 90 ||  angle / DEG_2_RAD == 270)
	{
		map->ray->y_dist = map->rend_dist + 10;
		return ;
	}
	//printf("This is Y function\n");
//	printf("angle = %f\n", angle / DEG_2_RAD);
 	if (angle / DEG_2_RAD < 270 && angle / DEG_2_RAD > 90)
	{
		//prev_y = map->ray->ray_y - (modulus_64(map->ray->ray_y) + 64);
		prev_y = floor(map->ray->ray_y / 64) * 64 + 64;
		delta_y = 64;
	}
	else
	{
		//prev_y = map->ray->ray_y - (modulus_64(map->ray->ray_y) - 1);
		prev_y = floor(map->ray->ray_y / 64) * 64 -1;
		delta_y = -64;
	}
	prev_x = floor(map->ray->ray_x + (map->ray->ray_y - prev_y) / tan (angle));
	// now finding the first Y grid works as well
	delta_x = 64 / tan(angle);
	printf("delta x = %f\n", delta_x);


	if ((int)prev_y / 64 < 0 || (int)prev_y / 64 > map->map_y_border || (int)prev_x / 64 < 0 || (int)prev_x / 64 > map->map_x_border)
	{
		map->ray->y_dist = map->rend_dist + 10;
		return ;
	}
	if (map->map[(int)prev_y / 64][(int)prev_x / 64] != '1')
	{
		while (true)
		{
			curr_x = (prev_x + delta_x);
			curr_y = (prev_y + delta_y);
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
 */

int	check_sq(int y, int x, char to_check, t_map *map)
{
	if (y / 64 < 0 || y / 64 > map->map_y_border || x / 64 < 0 || x / 64 > map->map_x_border)
	{
		//printf("out of bounds\n");
		return (1);
	}
	if (map->map[y / 64][x / 64] == to_check)
		return (1);
	return (0);
}
// was get x_dist
void	vertical_dist(t_map *map, float angle)
{
	int		ray_y;
	int		ray_x;
	float	delta_y;
	float  	delta_x;

  	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle > 2 * M_PI)
		angle -= 2 * M_PI; 
	if (angle / DEG_2_RAD == 270 ||  angle / DEG_2_RAD == 90)
	{
		map->ray->x_dist = map->rend_dist + 10;
		return ;
	}
	//right
 	if (angle / DEG_2_RAD > 270 || angle / DEG_2_RAD < 90)
	{
		ray_x = map->p_pos_x + (64 - modulus_64(map->p_pos_x));
		ray_y = map->p_pos_y + ((map->p_pos_x - ray_x) * tan(angle));
		delta_x = 64;
	}
	//left
	else 
	{
		ray_x = (map->p_pos_x - modulus_64(map->p_pos_x)) -1;
		ray_y = map->p_pos_y + ((map->p_pos_x - ray_x) * tan(angle));
		delta_x = -64;
	}
/* 	if (angle / DEG_2_RAD > 180)
		ray_y = map->p_pos_y - ((map->p_pos_x - ray_x) * tan(angle));
	else
		ray_y = map->p_pos_y + ((map->p_pos_x - ray_x) * tan(angle)); */

	delta_y = delta_x * tan(angle);
	while (check_sq(ray_y, ray_x, '1', map) == 0)
	{
		ray_x += delta_x;
		ray_y += delta_y;
	}
	map->ray->x_dist = sqrt(pow(map->p_pos_x - ray_x, 2) + pow(map->p_pos_y - ray_y, 2));
}
//was get y dist
void	horizontal_dist(t_map *map, float angle)
{
	int		ray_y;
	int		ray_x;
	float	delta_y;
	float  	delta_x;

  	if (angle < 0)
		angle += 2 * M_PI;
	else if (angle > 2 * M_PI)
		angle -= 2 * M_PI; 
	if (angle / DEG_2_RAD == 0 ||  angle / DEG_2_RAD == 180)
	{
		map->ray->y_dist = map->rend_dist + 10;
		return ;
	}
	//down
 	if (angle / DEG_2_RAD > 0 && angle / DEG_2_RAD < 180)
	{
		ray_y = map->p_pos_y + (64 - modulus_64(map->p_pos_y));
		ray_x = map->p_pos_x + ((map->p_pos_y - ray_y) / tan(angle));
		delta_y = 64;
	}
	//up
	else 
	{
		ray_y = (map->p_pos_y - modulus_64(map->p_pos_y)) -1;
		ray_x = map->p_pos_x + ((map->p_pos_y - ray_y) / tan(angle));
		delta_y = -64;
	}
/* 	if (angle / DEG_2_RAD > 270 || angle / DEG_2_RAD < 90)
		ray_x = map->p_pos_x + ((map->p_pos_y - ray_y) / tan(angle));
	else
		ray_x = map->p_pos_x - ((map->p_pos_y - ray_y) / tan(angle)); */
	delta_x = delta_y / tan(angle);
	while (check_sq(ray_y, ray_x, '1', map) == 0)
	{
		ray_x += delta_x;
		ray_y += delta_y;
	}
	map->ray->y_dist = sqrt(pow(map->p_pos_x - ray_x, 2) + pow(map->p_pos_y - ray_y, 2));
}

void	cast_wall(t_map *map, float dist, float deg, enum e_dir dir, int *row)
{
	int	top_pixel;
	int	pixels;
	int	color;
	unsigned int column_height;

	color = 0;
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
	while (pixels < (int)column_height && top_pixel + pixels < map->s_height)
		{
			mlx_put_pixel(map->images->world, (*row), top_pixel + pixels, color);
			pixels++;
		}
	(*row)++;
}

void	ray_caster(mlx_t *mlx, t_map *map, t_images *images)
{
	float	deg;
	int		row;
	float	angle;


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
		angle = map->p_orient + (deg * DEG_2_RAD);
		//printf("got here!\n");
		horizontal_dist(map, angle);
	//	map->ray->y_dist = 1000;
		//printf("got here2!\n");
	//	map->ray->x_dist = 1500;
		vertical_dist(map, angle);

		//printf("got here3!\n");

	if (map->ray->x_dist < map->ray->y_dist)
		map->ray->dist = map->ray->x_dist;
	else
		map->ray->dist = map->ray->y_dist;
	//printf("\n");
/* 	printf("y_dist = %f\n", map->ray->y_dist);
	printf("x_dist = %f\n", map->ray->x_dist);	*/
	//printf("player pos = [%d][%d]\n", map->p_pos_y, map->p_pos_x);
	//printf("DIST = %f\n", map->ray->y_dist); 
	//printf("ray angle is %f\n", map->p_orient / DEG_2_RAD + deg);
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
