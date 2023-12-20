/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ax <ax@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:02:17 by akhomche          #+#    #+#             */
/*   Updated: 2023/12/19 14:25:45 by ax               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup("")); 
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*fill_line_buffer(int fd, char *buffer, char *storage)
{
	char		*temp_storage_ptr;
	ssize_t		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(storage);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!storage)
			storage = ft_strdup("");
		temp_storage_ptr = storage;
		storage = ft_strjoin(temp_storage_ptr, buffer);
		free(temp_storage_ptr);
		temp_storage_ptr = NULL;
		if (ft_strchr(storage, '\n'))
			break ;
	}
	return (storage);
}

char	*extract_line_and_update_storage(char *line_buffer)
{
	char		*res;
	ssize_t		i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[1] == '\0')
		return (NULL);
	res = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*res == '\0')
	{
		free(res);
		res = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*storage[MAX_NUM_OF_FD];
	char		*buffer;
	char		*line;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0)	
	{
		free(storage[fd]);
		free(buffer);
		storage[fd] = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, buffer, storage[fd]);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	storage[fd] = extract_line_and_update_storage(line);
	return (line);
}