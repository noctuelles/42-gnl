#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	
	fd = open(argv[1], O_RDONLY);
	while (line = get_next_line(fd))
	{
		fputs(line, stdout);
		free(line);
	}
	return (0);
}
