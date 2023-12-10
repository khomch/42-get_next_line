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

char	*handle_file_read(int fd, char *buffer)
{
	char	*result;
	int		bytes_read;
	char	*temp_buffer;

	temp_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buffer)
		return (NULL);
	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		temp_buffer[bytes_read] = '\0';
		if (ft_strrchr(temp_buffer, '\n'))
		{
			result = ft_strjoin(buffer, temp_buffer);
			free(buffer);
			free(temp_buffer);
			return (result);
		}
		buffer = ft_strjoin(buffer, temp_buffer);
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	}
	if (ft_strlen(buffer) > 0)
		return (buffer);
	return (NULL);
}

char	*fill_line_buffer(int fd, char *storage)
{
	char	*buffer;	

	buffer = (char *)malloc(sizeof(char));
	if (!buffer)
		return (NULL);
	if (storage)
		buffer = ft_strdup(storage);
	if (ft_strrchr(buffer, '\n'))
		return (buffer);
	return (handle_file_read(fd, buffer));
}

char	*extract_line_from_buffer(char *line_buffer)
{
	char	*left_to_storage;
	int		i;
	int		j;
	int		x;
	int		len;

	len = ft_strlen(line_buffer);
	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	i++;
	left_to_storage = (char *)malloc(sizeof(char) * (len - i + 1));
	j = 0;
	x = i;
	while (line_buffer[i] != '\0')
	{
		left_to_storage[j] = line_buffer[i];
		i++;
		j++;
	}
	left_to_storage[j + 1] = '\0';
	line_buffer[x] = '\0';
	return (left_to_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	char		*line_buffer;

	if (!fd)
		return (NULL);
	line_buffer = fill_line_buffer(fd, storage);
	if (!line_buffer)
		return (NULL);
	storage = extract_line_from_buffer(line_buffer);
	return (line_buffer);
}

int	main(int argc, char const *argv[])
{
	int	fd;

	fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		printf("Error while open file\n");
		exit(1);
	}
	printf("✅ %s\n------------------------------------\n", get_next_line(fd));
	printf("✅ %s\n------------------------------------\n", get_next_line(fd));
	printf("✅ %s\n------------------------------------\n", get_next_line(fd));
	printf("✅ %s\n------------------------------------\n", get_next_line(fd));
	printf("✅ %s\n------------------------------------\n", get_next_line(fd));
	printf("✅ %s\n------------------------------------\n", get_next_line(fd));
	printf("✅ %s\n------------------------------------\n", get_next_line(fd));
	printf("✅ %s\n------------------------------------\n", get_next_line(fd));
	printf("✅ %s\n------------------------------------\n", get_next_line(fd));
	printf("✅ %s\n------------------------------------\n", get_next_line(fd));
	printf("✅ %s\n------------------------------------\n", get_next_line(fd));
	printf("✅ %s\n------------------------------------\n", get_next_line(fd));
	close(fd);
	return (0);
}

