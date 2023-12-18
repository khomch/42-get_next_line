/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ax <ax@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:02:17 by akhomche          #+#    #+#             */
/*   Updated: 2023/12/09 15:47:17 by ax               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < dstsize && dst[i])
	{
		i++;
	}
	while ((i + j + 1) < dstsize && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i != dstsize)
	{
		dst[i + j] = '\0';
	}
	return (i + ft_strlen(src));
}

char	*handle_file_read(int fd, char *buffer)
{
	char	*result;
	int		bytes_read;
	char	*temp_buffer;
	char	*save_buffer;

	temp_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buffer)
	{
		free(temp_buffer);
		return (NULL);
	}
	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		temp_buffer[bytes_read] = '\0';
		if (ft_strrchr(temp_buffer, '\n'))
		{
			result = ft_strjoin(buffer, temp_buffer);
			free(temp_buffer);
			return (result);
		}
		save_buffer = ft_strdup(buffer);
		buffer = ft_strjoin(save_buffer, temp_buffer);
		free(temp_buffer);
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	}
	if (ft_strlen(buffer) > 0)
	{
		return (buffer);
	}
	return (NULL);
}

char	*fill_line_buffer(int fd, char *storage)
{
	char	*buffer;
	char	*res;

	buffer = (char *)malloc(sizeof(char));
	if (!buffer)
	{
		return (NULL);
	}
	if (storage)
	{
		buffer = ft_strdup(storage);
		free(storage);
	}
	if (ft_strrchr(buffer, '\n'))
		return (buffer);
	res = handle_file_read(fd, buffer);
	free(buffer);
	return (res);
}

char	*get_line_from_buffer(char * line_buffer)
{
	char	*line;
	int		i;
	int		y;

	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	i++;
	line = (char *)malloc(sizeof(char) * (i));
	y = 0;
	while (y < i)
	{
		line[y] = line_buffer[y];
		y++;
	}
	line[y] = '\0';
	return (line);
}

char	*update_storage(int	line_len, char * line_buffer)
{
	char	*storage;
	int		i;
	int		y;

	storage = (char *)malloc(sizeof(char *) * (ft_strlen(line_buffer) - line_len + 1));
	i = line_len;
	y = 0;
	while(line_buffer[i])
	{
		storage[y] = line_buffer[i];
		y++;
		i++;
	}
	storage[y] = '\0';
	return (storage);
}


char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line_buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(storage);
		return (NULL);
	}
	line_buffer = fill_line_buffer(fd, storage);
	if (!line_buffer)
		return (NULL);
	result = get_line_from_buffer(line_buffer);
	storage = update_storage(ft_strlen(result), line_buffer);
	free(line_buffer);
	return (result);
}

// int	main(int argc, char const *argv[])
// {
// 	int	fd;
// 	char	*res;

// 	fd = open(argv[1], O_RDWR);
// 	if (fd == -1)
// 	{
// 		printf("Error while open file\n");
// 		exit(1);
// 	}
// 	res = get_next_line(fd);
// 	printf("✅ %s\n------------------------------------\n", res);
// 	free(res);
// 	res = get_next_line(fd);
// 	printf("✅ %s\n------------------------------------\n", res);
// 	free(res);
// 	res = get_next_line(fd);
// 	printf("✅ %s\n------------------------------------\n", res);
// 	free(res);
// 	// res = get_next_line(fd);
// 	// printf("✅ %s\n------------------------------------\n", res);
// 	// free(res);
// 	// res = get_next_line(fd);
// 	// printf("✅ %s\n------------------------------------\n", res);
// 	// res = get_next_line(fd);
// 	// free(res);
// 	// printf("✅ %s\n------------------------------------\n", res);
// 	// printf("✅ %s\n------------------------------------\n", get_next_line(fd));
// 	// printf("✅ %s\n------------------------------------\n", get_next_line(fd));
// 	// printf("✅ %s\n------------------------------------\n", get_next_line(fd));
// 	// printf("✅ %s\n------------------------------------\n", get_next_line(fd));
// 	// printf("✅ %s\n------------------------------------\n", get_next_line(fd));
// 	// printf("✅ %s\n------------------------------------\n", get_next_line(fd));
// 	// printf("✅ %s\n------------------------------------\n", get_next_line(fd));
// 	// printf("✅ %s\n------------------------------------\n", get_next_line(fd));
// 	// printf("✅ %s\n------------------------------------\n", get_next_line(fd));
// 	// printf("✅ %s\n------------------------------------\n", get_next_line(fd));
// 	// printf("✅ %s\n------------------------------------\n", get_next_line(fd));
// 	close(fd);
// 	return (0);
// }

