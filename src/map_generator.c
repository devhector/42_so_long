/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:30:03 by hectfern          #+#    #+#             */
/*   Updated: 2022/01/14 15:22:18 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

static int	find_sequece_newline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
		{
			printf("Error\nMap is wrong format\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static char	*read_file(int fd)
{
	char	*map;
	char	*temp;

	map = ft_strdup("");
	if (!map)
		return (NULL);
	while (42)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		map = ft_strjoin(map, temp);
		free(temp);
	}
	close(fd);
	return (map);
}

char	**map_generator(char *path)
{
	int		fd;
	char	*map;
	char	**map_array;

	if (!ext_validator(path))
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nFile not found\n");
		return (NULL);
	}
	map = read_file(fd);
	if (!map)
		return (NULL);
	if (!find_sequece_newline(map))
	{
		free(map);
		return (NULL);
	}
	map_array = ft_split(map, '\n');
	free(map);
	return (map_array);
}
