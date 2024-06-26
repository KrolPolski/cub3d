/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:04:25 by clundber          #+#    #+#             */
/*   Updated: 2024/05/14 14:38:01 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ret_error(char *str)
{
	ft_putendl_fd(str, 2);
	return (1);
}

void	free_2d(char **ptr)
{
	int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
		{
			free(ptr[i]);
			ptr[i] = NULL;
			i++;
		}
		free(ptr);
		ptr = NULL;
	}
}

void	ft_nullfree(char *str)
{
	if (str)
	{
		free (str);
		str = NULL;
	}
}
