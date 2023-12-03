/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ax <ax@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:02:17 by akhomche          #+#    #+#             */
/*   Updated: 2023/11/26 19:39:01 by ax               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (i < len && s[i] != '\0')
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	write_start(char *current, char *start, int j)
{
	int	len;
	int	x;

	x = 0;
	len = ft_strlen(current);
	while (j > 0)
	{
		start[x] = current[len - j];
		x++;
		j--;
	}
	start[x] = '\0';
}

int	check_if_end_of_line(char *buffer, char *current, char *start)
{
	int			i;
	int			j;

	if (ft_strrchr(current, '\n'))
	{
		i = ft_strlen(buffer);
		j = 0;
		while (--i >= 0 && buffer[i] != '\n')
		{
			buffer[i] = 0;
			j++;
		}
		ft_putstr(buffer);
		write_start(current, start, j);
		return (1);
	}
	return (0);
}

char	*write_one_line(char *src)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!res)
		return (NULL);
	if (ft_strrchr(src, '\n')) {
		while (src[i] || src[i] != '\n')
		{
			res[i] = src[i];
			i++;
		}		
	}
	res[i] = '\0';
	return (res);
}

char	*get_next_line_1(int fd)
{
	static char	start[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*buffer;
	char		current[BUFFER_SIZE + 1];

	bytes_read = read(fd, current, BUFFER_SIZE);
	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	while (bytes_read > 0 || (bytes_read == 0 && ft_strlen(buffer) > 0))
	{
		current[bytes_read] = '\0';
		if (ft_strlen(start) > 0)
		{
			ft_strlcat(buffer, start, sizeof(buffer));
			ft_bzero(start, sizeof(start));
		}
		ft_strlcat(buffer, current, ft_strlen(buffer) + ft_strlen(current) + 1);
		if (check_if_end_of_line(buffer, current, start))
			return (ft_strdup(buffer));
		bytes_read = read(fd, current, BUFFER_SIZE);
	}
	free(buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	start[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*buffer;
	char		current[BUFFER_SIZE + 1];

	if (ft_strlen(start))
	{
		ft_putstr("\nHERE\n");
		ft_putstr(start);
		ft_putstr("\nHERE\n");
		ft_putstr(write_one_line(start));
		return (NULL);
	}

	bytes_read = read(fd, current, BUFFER_SIZE);
	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	while (bytes_read > 0 || (bytes_read == 0 && ft_strlen(buffer) > 0))
	{
		current[bytes_read] = '\0';
		// if (ft_strlen(start) > 0)
		// {
		// 	ft_strlcat(buffer, start, sizeof(buffer));
		// 	ft_bzero(start, sizeof(start));
		// }
		// ft_strlcat(buffer, current, ft_strlen(buffer) + ft_strlen(current) + 1);
		if (check_if_end_of_line(buffer, current, start))
			return (ft_strdup(buffer));
		bytes_read = read(fd, current, BUFFER_SIZE);
	}
	free(buffer);
	return (NULL);
}

int	main(int argc, char const *argv[])
{
	int		fd;

	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		printf("Error while open file\n");
		exit(1);
	}
	printf("RES: %s", get_next_line(fd));
	printf("RES: %s", get_next_line(fd));
	// printf("RES: %s", get_next_line(fd));
	// printf("RES: %s", get_next_line(fd));
	// printf("RES: %s", get_next_line(fd));
	close(fd);
	return (0);
}
