#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	char	*file;
	int		fd;
	char	*line;

	file = "hello.txt";
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("Error while opening file");
		return (1);
	}
	printf("\nOPEN FILE DESCRIPTOR: %d\n\n", fd);
	line = get_next_line(fd);
    while(line)
    {	
        printf("%s\n", line);
        line = get_next_line(fd);
    }
    printf("%s\n", line);
    line = get_next_line(fd);

	return (0);
}