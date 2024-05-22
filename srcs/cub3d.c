/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:45:09 by clundber          #+#    #+#             */
/*   Updated: 2024/05/22 09:47:09 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_data(t_map *map)
{
	map->map = NULL;
	map->p_pos_x = 0;
	map->p_pos_y = 0;
	map->p_orient = 0;
	map->ceiling = malloc(sizeof(int *) * 5);
	map->ceiling[0] = -1;
	map->ceiling[1] = -1;
	map->ceiling[2] = -1;
	map->ceiling[3] = 0;
	map->floor = malloc(sizeof(int *) * 5);
	map->floor[0] = -1;
	map->floor[1] = -1;
	map->floor[2] = -1;
	map->floor[3] = 0;
	map->text[0] = NULL;
	map->text[1] = NULL;
	map->text[2] = NULL;
	map->text[3] = NULL;
	map->text[4] = NULL;
	map->mapstart = -1;
	map->map_visible = false;
}
int	main(int argc, char *argv[])
{
	t_map map;

	init_data(&map);
	if (parsing(argc, argv, &map) != 0)
		return (1);
	cub3d_mlx(&map);
	//cleanup
	printf("great success\n");
	return(0);
}

/* 
allowed functions: • open, close, read, write,
printf, malloc, free, perror,
strerror, exit
• All functions of the math
library (-lm man man 3 math)
• All functions of the MinilibX
+ what is needed for bonuses

must take in a scene configuration file in format *.cub

◦ Each element (except the map) firsts information is the type identifier (composed by one or two character(s)), followed by all specific informations for each
object in a strict order such as :
∗ North texture:
NO ./path_to_the_north_texture
· identifier: NO
· path to the north texure
∗ South texture:
SO ./path_to_the_south_texture
· identifier: SO
· path to the south texure
∗ West texture:
WE ./path_to_the_west_texture
· identifier: WE
· path to the west texure
∗ East texture:
EA ./path_to_the_east_texture
· identifier: EA
· path to the east texure
∗ Floor color:
F 220,100,0
· identifier: F
· R,G,B colors in range [0,255]: 0, 255, 255
8
cub3D My first RayCaster with miniLibX
∗ Ceiling color:
C 225,30,0
· identifier: C
· R,G,B colors in range [0,255]: 0, 255, 255
 */