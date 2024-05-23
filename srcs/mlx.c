/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:58:50 by rboudwin          #+#    #+#             */
/*   Updated: 2024/05/23 15:07:38 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*void	draw_view(mlx_t *mlx, t_map *map, t_images *images)
{
	int i;
	
	i = 0;
	mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient + 30 * DEG_2_RAD), images->plyr->height /2 - i * cos(map->p_orient + 30 * DEG_2_RAD), get_rgba(255, 0, 255, 255));
	mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient - 30 * DEG_2_RAD), images->plyr->height /2 - i * cos(map->p_orient - 30 * DEG_2_RAD), get_rgba(255, 0, 255, 255));

}*/
/* Draws lines on the minimap, to indicate a 60 degree field of view relative to the players orientation */
void	draw_direction(mlx_t *mlx, t_map *map, t_images *images)
{
	int i;
	(void)mlx;
	(void)map;
	i = 0;
	mlx_delete_image(mlx, images->plyr);
	images->plyr = mlx_texture_to_image(mlx, images->player);
	mlx_image_to_window(mlx, images->plyr, map->p_pos_x, map->p_pos_y);
	while (i < 30)
	{
		mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient), images->plyr->height /2 - i * cos(map->p_orient), get_rgba(255, 0, 0, 255));
		mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient + 30 * DEG_2_RAD), images->plyr->height /2 - i * cos(map->p_orient + 30 * DEG_2_RAD), get_rgba(255, 0, 255, 255));
		mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient - 30 * DEG_2_RAD), images->plyr->height /2 - i * cos(map->p_orient - 30 * DEG_2_RAD), get_rgba(255, 0, 255, 255));
		mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient + 15 * DEG_2_RAD), images->plyr->height /2 - i * cos(map->p_orient + 15 * DEG_2_RAD), get_rgba(255, 0, 255, 255));
		mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient - 15 * DEG_2_RAD), images->plyr->height /2 - i * cos(map->p_orient - 15 * DEG_2_RAD), get_rgba(255, 0, 255, 255));
		
		i++;
	}
}
/* draws a top down map */
void	draw_2d_map(mlx_t *mlx, t_map *map, t_images *images)
{
	int			i;
	int			k;
	int			x;
	int			y;

	images->black = mlx_load_png("assets/black.png");
	images->white = mlx_load_png("assets/white.png");
	images->player = mlx_load_png("assets/player.png");
	images->blk = mlx_texture_to_image(mlx, images->black);
	images->wht = mlx_texture_to_image(mlx, images->white);
	images->plyr = mlx_texture_to_image(mlx, images->player);
	images->dir = mlx_new_image(mlx, 64, 64);
	images->bg = mlx_new_image(mlx, map->s_width, map->s_height);
	ft_memset(images->bg->pixels, 180, images->bg->width
		* images->bg->height * BPP);
	mlx_image_to_window(mlx, images->bg, 0, 0);
	i = 0;
	k = 0;
	x = 0;
	y = 0;
	printf("About to enter map printing loop\n");
 	while (map->map[i])
	{
		while (map->map[i][k])
		{
			if (map->map[i][k] == '1')
			{
				mlx_image_to_window(mlx, images->blk, (k + 1) * 64, (i + 1) * 64);
			}
			else if (map->map[i][k] == 'N')
			{
				map->p_pos_x = ((k + 1) * 64);
				map->p_pos_y = ((i + 1) * 64);
				map->p_orient = 0;
				mlx_image_to_window(mlx, images->wht, (k + 1) * 64, (i + 1) * 64);
			}
			else if (map->map[i][k] == 'S')
			{
				map->p_pos_x = ((k + 1) * 64);
				map->p_pos_y = ((i + 1) * 64);
				map->p_orient = 180 * DEG_2_RAD;
				mlx_image_to_window(mlx, images->wht, (k + 1) * 64, (i + 1) * 64);
			}
			else if (map->map[i][k] == 'E')
			{
				map->p_pos_x = ((k + 1) * 64);
				map->p_pos_y = ((i + 1) * 64);
				map->p_orient = 90 * DEG_2_RAD;
				mlx_image_to_window(mlx, images->wht, (k + 1) * 64, (i + 1) * 64);
			}
			else if (map->map[i][k] == 'W')
			{
				map->p_pos_x = ((k + 1) * 64);
				map->p_pos_y = ((i + 1) * 64);
				map->p_orient = 270 * DEG_2_RAD;
				mlx_image_to_window(mlx, images->wht, (k + 1) * 64, (i + 1) * 64);
			}
			else if (map->map[i][k] == '0')
				mlx_image_to_window(mlx, images->wht, (k + 1) * 64, (i + 1) * 64);
			k++;
		}
		k = 0;
		i++;	
	}
	mlx_image_to_window(mlx, images->plyr, map->p_pos_x, map->p_pos_y);
	ray_caster(mlx, map, images);

	//draw_direction(mlx, map, images);
	images->blk->enabled = false;
	images->wht->enabled = false;
	images->plyr->enabled = false;
	images->fg->enabled = false;
}

void	move_forward(t_map *map)
{
	//printf("We are in a '%c' square\n", detect_square(map, map->p_pos_x, map->p_pos_y));
	if (detect_square(map, map->p_pos_x + round(5 * sin(map->p_orient)), map->p_pos_y - round(5 * cos(map->p_orient))) != '1')
	{
		map->p_pos_x += round(5 * sin(map->p_orient));
		map->p_pos_y -= round(5 * cos(map->p_orient));
	//	map->images->plyr->instances[0].x += round(5 * sin(map->p_orient));
	//	map->images->plyr->instances[0].y -= round(5 * cos(map->p_orient));
	}
	//else
	//	printf("Hello wall my old friend\n");
}
void	move_backward(t_map *map)
{
	//printf("We are in a '%c' square\n", detect_square(map, map->p_pos_x, map->p_pos_y));
	if (detect_square(map, map->p_pos_x - round(5 * sin(map->p_orient)), map->p_pos_y + round(5 * cos(map->p_orient))) != '1')
	{
		map->p_pos_x -= round(5 * sin(map->p_orient));
		map->p_pos_y += round(5 * cos(map->p_orient));
	//	map->images->plyr->instances[0].x -= round(5 * sin(map->p_orient));
	//	map->images->plyr->instances[0].y += round(5 * cos(map->p_orient));
	}
	//else
	//	printf("Hello wall my old friend\n");
}
void	move_left(t_map *map)
{
	//printf("We are in a '%c' square\n", detect_square(map, map->p_pos_x, map->p_pos_y));
	if (detect_square(map, map->p_pos_x + round(5 * sin(map->p_orient - 90 * DEG_2_RAD)), map->p_pos_y - round(5 * cos(map->p_orient - 90 * DEG_2_RAD))) != '1')
	{
		map->p_pos_x += round(5 * sin(map->p_orient - 90 * DEG_2_RAD));
		map->p_pos_y -= round(5 * cos(map->p_orient - 90 * DEG_2_RAD));
	//	map->images->plyr->instances[0].x += round(5 * sin(map->p_orient - 90 * DEG_2_RAD));
	//	map->images->plyr->instances[0].y -= round(5 * cos(map->p_orient - 90 * DEG_2_RAD));
	}
	//else
	//	printf("Hello wall my old friend\n");
}

void	move_right(t_map *map)
{
	//printf("We are in a '%c' square\n", detect_square(map, map->p_pos_x, map->p_pos_y));
	if (detect_square(map, map->p_pos_x + round(5 * sin(map->p_orient + 90 * DEG_2_RAD)), map->p_pos_y - round(5 * cos(map->p_orient + 90 * DEG_2_RAD))) != '1')
	{
		map->p_pos_x += round(5 * sin(map->p_orient + 90 * DEG_2_RAD));
		map->p_pos_y -= round(5 * cos(map->p_orient + 90 * DEG_2_RAD));
	//	map->images->plyr->instances[0].x += round(5 * sin(map->p_orient + 90 * DEG_2_RAD));
	//	map->images->plyr->instances[0].y -= round(5 * cos(map->p_orient + 90 * DEG_2_RAD));
	}
	//else
	//	printf("Hello wall my old friend\n");
}
void	ft_movehook(void *param)
{
	t_map *map;

	map = (t_map *)param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W) || mlx_is_key_down(map->mlx, MLX_KEY_UP))
	{
		move_forward(map);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_S) || mlx_is_key_down(map->mlx, MLX_KEY_DOWN))
	{
		move_backward(map);
	}

	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	{
		move_left(map);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	{
		move_right(map);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->p_orient -= 2 * DEG_2_RAD;
		if (map->p_orient <= 0)
			map->p_orient += 2 * M_PI;
		//printf("Degrees: %f\n", map->p_orient / DEG_2_RAD);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->p_orient += 2 * DEG_2_RAD;
		if (map->p_orient >= 2 * M_PI)
			map->p_orient -= 2 * M_PI;
		//printf("Degrees: %f\n", map->p_orient / DEG_2_RAD);
	}
	ray_caster(map->mlx, map, map->images);
	
}
void	ft_single_press_hook(mlx_key_data_t keydata, void *param)
{
t_map *map;

map = (t_map *)param;
if	(((keydata.key == MLX_KEY_M)
		&& keydata.action == MLX_PRESS))
	{
		if (map->map_visible)
		{
			map->map_visible = false;
			map->images->blk->enabled = false;
			map->images->wht->enabled = false;
			map->images->plyr->enabled = false;
			map->images->fg->enabled = false;
		}
		else
		{
			map->map_visible = true;
			map->images->blk->enabled = true;
			map->images->wht->enabled = true;
			map->images->plyr->enabled = true;
			map->images->fg->enabled = true;
			
		}
	}
}

int cub3d_mlx(t_map *map)
{
	int			i;
	mlx_t		*mlx;
	t_images	images;

	map->images = &images;
	i = 0;
	map->s_width = 800;//1920;//320;//2560;
	map->s_height = 600;//1080;//1440;
	map->fov_angle = 60;
	map->proj_plane = (map->s_width / 2) / tan((map->fov_angle /2) * DEG_2_RAD);
	map->rend_dist = 700; //512;
	mlx = mlx_init(map->s_width, map->s_height, "cub3d", true);
	map->mlx = mlx;
	draw_2d_map(mlx, map, &images);
	map->x_offset = 64;
	map->y_offset = 64;

	mlx_key_hook(mlx, ft_single_press_hook, map);
	ray_caster(mlx, map, map->images);
	mlx_loop_hook(mlx, ft_movehook, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_2d(map->map);
	return (EXIT_SUCCESS);
}