/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:45:09 by clundber          #+#    #+#             */
/*   Updated: 2024/05/13 12:20:10 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char *argv[])
{
	//parse input
	//start MLX loop
	//cleanup
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