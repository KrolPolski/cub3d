/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:58:50 by rboudwin          #+#    #+#             */
/*   Updated: 2024/05/15 14:24:29 by rboudwin         ###   ########.fr       */
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
		//printf("attempting to draw direction\n");
		//this draws straight north
		//mlx_put_pixel(images->plyr, images->plyr->width / 2, i, get_rgba(255, 0, 0, 255));
		mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient), images->plyr->height /2 - i * cos(map->p_orient), get_rgba(255, 0, 0, 255));
		mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient + 30 * DEG_2_RAD), images->plyr->height /2 - i * cos(map->p_orient + 30 * DEG_2_RAD), get_rgba(255, 0, 255, 255));
		mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient - 30 * DEG_2_RAD), images->plyr->height /2 - i * cos(map->p_orient - 30 * DEG_2_RAD), get_rgba(255, 0, 255, 255));
		mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient + 15 * DEG_2_RAD), images->plyr->height /2 - i * cos(map->p_orient + 15 * DEG_2_RAD), get_rgba(255, 0, 255, 255));
		mlx_put_pixel(images->plyr, images->plyr->width / 2 + i * sin(map->p_orient - 15 * DEG_2_RAD), images->plyr->height /2 - i * cos(map->p_orient - 15 * DEG_2_RAD), get_rgba(255, 0, 255, 255));
		
		i++;
	}
}
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
	//mlx_resize_image(images->plyr, 8, 8);
	images->bg = mlx_new_image(mlx, 2560, 1440);
	ft_memset(images->bg->pixels, 180, images->bg->width * images->bg->height * BPP);
	mlx_image_to_window(mlx, images->bg, 0, 0);
	i = 0;
	k = 0;
	x = 0;
	y = 0;
	//mlx_image_to_window(mlx, black, 500, 500);
	printf("About to enter map printing loop\n");
	while (map->map[i])
	{
		while (map->map[i][k])
		{
			if (map->map[i][k] == '1')
			{
				printf("map->map[%d][%d] is %c so placing black img\n", i, k, map->map[i][k]);
				mlx_image_to_window(mlx, images->blk, (k + 1) * 64, (i + 1) * 64);
			}
			else if (map->map[i][k] == 'N')
			{
				map->p_pos_x = ((k + 1) * 64) + 32;
				map->p_pos_y = ((i + 1) * 64) + 32;
				map->p_orient = 0;
				mlx_image_to_window(mlx, images->wht, (k + 1) * 64, (i + 1) * 64);
			}	
			else if (map->map[i][k] == '0')
				mlx_image_to_window(mlx, images->wht, (k + 1) * 64, (i + 1) * 64);
			k++;
		}
		k = 0;
		i++;	
	}
	mlx_image_to_window(mlx, images->plyr, map->p_pos_x - 32, map->p_pos_y - 32);
	draw_direction(mlx, map, images);
}

char	detect_square(t_map *map, char dir)
{
	int relative_x;
	int	relative_y;
	int remainder_x;
	int remainder_y;
	//remainder_x = (map->p_pos_x - map->x_offset) % 64;
	//remainder_y = (map->p_pos_y - map->x_offset) % 64;
	relative_x = ((map->p_pos_x - map->x_offset + 30) / 64); 
	relative_y = ((map->p_pos_y - map->y_offset + 30) / 64);
	printf("Our current square is a '%c'\n", map->map[relative_y][relative_x]);
	printf("And our relative_x is %d and relative_y is %d\n", relative_x, relative_y);
	//if (dir == 'N')
	//	relative_y-= 1;
	//if (dir == 'S')
	//	relative_y+= 1;	
	//else if (dir == 'W')
	//	relative_x-= 1;
	//else if (dir == 'E')
	//	relative_x+= 1;
	printf("for next square relative_x is %d and relative_y is %d\n", relative_x, relative_y);
	printf("because p_pos_x and p_pos_y are %d, %d\n", map->p_pos_x, map->p_pos_y);
	return (map->map[relative_y][relative_x]);
}
void	ft_movehook(void *param)
{
	t_map *map;

	map = (t_map *)param;
	if (mlx_is_key_down(map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map->mlx);
	if (mlx_is_key_down(map->mlx, MLX_KEY_W))
	{
		//printf("The square to the north is a %c\n", detect_square(map, 'N'));
	//	if (detect_square(map, 'N') != '1')
		map->p_pos_y -= 5;
		map->images->plyr->instances[0].y -= 5;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_S))
	{
		//	printf("The square to the south is a %c\n", detect_square(map, 'S'));
		//if (detect_square(map, 'S') != '1')
		
		map->p_pos_y += 5;
		map->images->plyr->instances[0].y += 5;
	}

	if (mlx_is_key_down(map->mlx, MLX_KEY_A))
	{
		//printf("The square to the west is a %c\n", detect_square(map, 'W'));
		//if (detect_square(map, 'W') != '1'){
		
		map->p_pos_x -= 5;
		map->images->plyr->instances[0].x -= 5;//}
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_D))
	{
		//printf("The square to the east is a %c\n", detect_square(map, 'E'));
		//if (detect_square(map, 'E') != '1'){
		map->p_pos_x += 5;
		map->images->plyr->instances[0].x += 5;
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_LEFT))
	{
		map->p_orient -= 1 * DEG_2_RAD;
		if (map->p_orient <= 0)
			map->p_orient += 2 * M_PI;
		printf("Degrees: %f\n", map->p_orient / DEG_2_RAD);
		draw_direction(map->mlx, map, map->images);
	}
	if (mlx_is_key_down(map->mlx, MLX_KEY_RIGHT))
	{
		map->p_orient += 1 * DEG_2_RAD;
		if (map->p_orient >= 2 * M_PI)
			map->p_orient -= 2 * M_PI;
		printf("Degrees: %f\n", map->p_orient / DEG_2_RAD);
		draw_direction(map->mlx, map, map->images);
	}
}

int cub3d_mlx(t_map *map)
{
	mlx_t	*mlx;
	t_images images;
	
	map->images = &images;
	/*map->map = ft_calloc(10, sizeof(char *));
	map->map[0] = ft_strdup("111111111");
	map->map[1] = ft_strdup("100000001");
	map->map[2] = ft_strdup("100000001");
	map->map[3] = ft_strdup("100000001");
	map->map[4] = ft_strdup("1000N0001");
	map->map[5] = ft_strdup("100101001");
	map->map[6] = ft_strdup("100111001");
	map->map[7] = ft_strdup("100000001");
	map->map[8] = ft_strdup("111111111");
	map->map[9] = NULL;*/
	
	int i;
	i = 0;
	/*while (map->map[i])
	{
		printf("Line %d is: %s\n", i, map->map[i]);
		i++;
	}*/
		
	mlx = mlx_init(2560, 1440, "cub3d", true);
	map->mlx = mlx;
	draw_2d_map(mlx, map, &images);
	map->x_offset = 64;
	map->y_offset = 64;
	mlx_loop_hook(mlx, ft_movehook, map);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	free_2d(map->map);
	return (EXIT_SUCCESS);
}