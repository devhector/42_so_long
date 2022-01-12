/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 17:30:03 by hectfern          #+#    #+#             */
/*   Updated: 2022/01/08 17:48:42 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/so_long.h"

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
	map_array = ft_split(map, '\n');
	free(map);
	return (map_array);
}
