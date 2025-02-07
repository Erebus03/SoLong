#include "../gnl/get_next_line.h"
# include <string.h>
#include <stdio.h>
#include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

int main()
{
	int fd = open("map.ber", O_RDONLY);

	char *line;
	int r = 0;
	line = get_next_line(fd);
	printf("<%s>\n", line);
}