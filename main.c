#include "get_next_line.h"

int	main(int argc, char const *argv[])
{
	int	fd;
	char	*res;

	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		printf("Error while open file\n");
		exit(1);
	}
	res = get_next_line(fd);
	printf("✅ %s\n------------------------------------\n", res);
	free(res);
	res = get_next_line(fd);
	printf("✅ %s\n------------------------------------\n", res);
	free(res);
	res = get_next_line(fd);
	printf("✅ %s\n------------------------------------\n", res);
	free(res);
	// res = get_next_line(fd);
	// printf("✅ %s\n------------------------------------\n", res);
	// free(res);
	// res = get_next_line(fd);
	// printf("✅ %s\n------------------------------------\n", res);
	// res = get_next_line(fd);
	close(fd);
	return (0);
}
