#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char **map_generator(char *path)
{
	int fd;
	char *map;
	char *temp;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error: file not found\n");
		return (NULL);
	}
	temp = NULL;
	map = ft_strdup("");

	while (!!(temp = get_next_line(fd)))
	{
		map = ft_strjoin(map, temp);
		free(temp);
	}
	close(fd);
	return (ft_split(map, '\n'));
}

int main(int argc, char **argv)
{
	char **map;
	int i;

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
	return (0);
}