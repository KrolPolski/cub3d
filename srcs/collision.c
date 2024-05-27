/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:46:42 by rboudwin          #+#    #+#             */
/*   Updated: 2024/05/25 12:58:56 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	detect_square(t_map *map, int x, int y)
{
	char	sq;
	int		rel_x;
	int		rel_y;
 
	rel_x = x / 64;
	rel_y = y / 64;

	sq = map->map[rel_y][rel_x];
	return (sq);
}
