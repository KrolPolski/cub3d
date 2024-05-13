/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clundber <clundber@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:02:13 by clundber          #+#    #+#             */
/*   Updated: 2024/05/13 16:17:11 by clundber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_name(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
		i++;
	if (i <= 4)
		return (1);
	if (ft_strncmp(&str[i -4], ".cub", 5) != 0)
		return (1);
	return (0);

}

int	ft_empty(char *line)
{
	while (*line && ((*line >= 9 && *line <= 13) || *line == 32))
		line++;
	if (*line == '\0' || *line == '\n')
		return (0);
	return (1);
}
int	ft_ismap(char *line)
{
	while (*line && (*line == ' ' || *line == '1' || *line == '0' || *line == 'N' \
		|| *line == 'S' || *line == 'E' || *line == 'W'))
		line++;
	if (*line == '\0' || *line == '\n')
		return (0);
	return (1);
}

// need to add amlloc checks
int	check_line(char *line, t_map *map)
{
	if (ft_empty(line) == 0)
	{
		if (map->mapstart < 0)
			return (0);
		else
			return (1);
	}
	if (ft_strncmp(line, "NO ./", 5) == 0)
	{
		if (!map->no_text)
			map->no_text = ft_substr(line, 5, -1);
		else
			return (1);
	}
	else if (ft_strncmp(line, "SO ./", 5) == 0)	
	{
		if (!map->so_text)
			map->so_text = ft_substr(line, 5, -1);
		else
			return (1);
	}
	else if (ft_strncmp(line, "WE ./", 5) == 0)	
	{
		if (!map->we_text)
			map->we_text = ft_substr(line, 5, -1);
		else
			return (1);
	}
	else if (ft_strncmp(line, "EA ./", 5) == 0)
	{
		if (!map->ea_text)
			map->ea_text = ft_substr(line, 5, -1);
		else
			return (1);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (!map->floor)
			map->floor = ft_substr(line, 2, -1);
		else
			return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (!map->ceiling)
			map->ceiling = ft_substr(line, 2, -1);
		else
			return (1);
	}
	else if (ft_ismap(line) == 0)
	{
		if (map->mapstart < 0)
			map->mapstart = 1;
		return (0);
	}
	else
	{
		printf("invalid map triggered\n");
		return (1);
	}
	return (0);
}

int	extract_data(char *arg, t_map *map)
{
	char	*buffer;
	int		fd;
	char	*map_str;

	map_str = NULL;
	fd = 0;
	buffer = NULL;
	fd = open(arg, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		return (1);
	}
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		if (check_line(buffer, map) != 0)
			return (1);
		if (map->mapstart > 0)
		{
			if (!map_str)
				map_str = ft_strdup(buffer);
			else
				map_str = ft_strjoin(map_str, buffer); //this will leak for now
			if (!map_str)
				return (1); //needs malloc error func
		}
	}
	printf("map str = \n%s\n", map_str);
	map->map = ft_split(map_str, '\n');
	return (0);
}
int	parsing(int argc, char **argv, t_map *map)
{
	if (argc != 2 || !argv || !argv[1] || !argv[1][0])
		return (ret_error("invalid arguments"));
	if (check_name(argv[1]) != 0)
		return (ret_error("invalid argument name"));
	if (extract_data(argv[1], map) != 0)
		return (1);
	return (0);

}
