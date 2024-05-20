/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:46:42 by rboudwin          #+#    #+#             */
/*   Updated: 2024/05/20 18:18:03 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	detect_square(t_map *map, int x, int y)
{
	char	sq;
	int		rel_x;
	int		rel_y;
 
	rel_x = (x - 17) / 32;
	rel_y = (y - 17) / 32;

	sq = map->map[rel_y][rel_x];
	return (sq);
}
