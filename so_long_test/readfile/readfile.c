/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hectfern <hectfern@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 23:08:49 by hectfern          #+#    #+#             */
/*   Updated: 2022/01/03 23:14:01 by hectfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char	**map_generator(char *path)
{
	int		fd;
	char	*map;
	char	*temp;
	char	**map_array;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: file not found\n");
		return (NULL);
	}
	temp = NULL;
	map = ft_strdup("");
	while (42)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		map = ft_strjoin(map, temp);
		free(temp);
	}
	close(fd);
	map_array = ft_split(map, '\n');
	free(map);
	return (map_array);
}

int	main(int argc, char **argv)
{
	char	**map;
	int		count;
	int		i;

	if (argc != 2)
	{
		printf("Usage: ./map_generator <map_file>\n");
		return (0);
	}
	map = map_generator(argv[1]);
	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
	count = 0;
	while (map[count])
		free(map[count++]);
	free(map);
	return (0);
}
