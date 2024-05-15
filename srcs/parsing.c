/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 12:02:13 by clundber          #+#    #+#             */
/*   Updated: 2024/05/15 14:11:03 by rboudwin         ###   ########.fr       */
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

int	get_color(int *arr, char *str)
{
	int	i;

	i = 0;
	str++;
	str++;
	ft_atoi(str);
	arr[0] = ft_atoi(str);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	if (*str && *str == ',')
		str++;
	arr[1] = ft_atoi(str);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	if (str && *str == ',')
		str++;
	arr[2] = ft_atoi(str);
	while (*str && (*str >= '0' && *str <= '9'))
		str++;
	arr[3] = 1;
	if (*str == '\0' || *str == '\n')
		return (0);
	return (1);
}

char *get_path(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	return (ft_substr(line, 3, i -3));
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
		if (!map->text[0])
			map->text[0] = get_path(line);
		else
			return (1);
	}
	else if (ft_strncmp(line, "SO ./", 5) == 0)	
	{
		if (!map->text[2])
			map->text[2] = get_path(line);
		else
			return (1);
	}
	else if (ft_strncmp(line, "WE ./", 5) == 0)	
	{
		if (!map->text[3])
			map->text[3] = get_path(line);
		else
			return (1);
	}
	else if (ft_strncmp(line, "EA ./", 5) == 0)
	{
		if (!map->text[1])
			map->text[1] = get_path(line);
		else
			return (1);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (map->floor[3] == 0)
		{
			if (get_color(map->floor, line) == 1)
				return (1);
		}
		else
			return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (map->ceiling[3] == 0)
		{
			if (get_color(map->ceiling, line) == 1)
				return (1);
		}
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

int	map_init(char **temp_map, t_map *map)
{
	int	x;
	int	y;
	int	max;

	y = 0;
	max = 0;
	while (temp_map[y])
	{
		x = 0;
		while (temp_map[y][x])
			x++;
		if (x > max)
			max = x;
		y++;
	}
	map->map = ft_calloc((y +1), sizeof(char *));
	x = 0;
	while (x < y)
	{
		map->map[x] = ft_calloc(max + 1, sizeof(char));
		x++;
	}
	//printf("We decided the max was %d\n", max);
	return (0);
}

int	map_parse(char *map_str, t_map *map)
{
	char	**temp_map;
	int		x;
	int		y;
	int		max;

	max = 0;
	y = 0;
	temp_map = NULL;
	temp_map = ft_split(map_str, '\n');
	if (!temp_map)
		return(ret_error("malloc failed"));
	ft_nullfree(map_str);
	map_init(temp_map, map);
	while (temp_map[y])
	{
		x = 0;
		while (temp_map[y][x])
		{
			map->map[y][x] = temp_map[y][x];
			x++;
		}
		temp_map[y][x] = '\0';
		y++;
	}
	temp_map[y] = NULL;
	y = 0;
	while (temp_map[y])
	{
		printf("Map: %s\n", temp_map[y]);
		y++;
	}
	//printf("This will probably segfault()")
	free_2d(temp_map);
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
		ft_nullfree(buffer);
	}
	map_parse(map_str, map);
	return (0);
}

int	validate_data(t_map *map)
{
	int	i;
	int	fd;

	fd = 0;
	i = 0;
	if (map->ceiling[0] < 0 || map->ceiling[1] < 0 || map->ceiling[2] < 0 || map->floor[0] < 0 || \
		map->floor[1] < 0 || map->floor[2] < 0)
		return (ret_error("invalid floor/ceiling color"));
	while (i < 4)
	{
		fd = open(map->text[i], O_RDONLY);
		if (fd < 0)
		{
			perror("Error");
			return (1);
		}
		else
			close(fd);
		i++;
	}
	return (0);
}

int	parsing(int argc, char **argv, t_map *map)
{
	if (argc != 2 || !argv || !argv[1] || !argv[1][0])
		return (ret_error("invalid arguments"));
	if (check_name(argv[1]) != 0)
		return (ret_error("invalid argument name"));
	if (extract_data(argv[1], map) != 0)
		return (ret_error("invalid file data"));
	//printf("%s\n", map->text[0]);
	if (validate_data(map) != 0)
		return (1);
	return (0);
}
