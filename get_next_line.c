/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhomche <akhomche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:02:17 by akhomche          #+#    #+#             */
/*   Updated: 2024/01/22 14:28:14 by akhomche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_start_len;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	s_start_len = ft_strlen(s + start);
	if (len > s_start_len)
		len = s_start_len;
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

static char	*fill_line(int fd, char *buffer, char *storage)
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

static char	*update_line_and_set_storage(char *line_buffer)
{
	char		*updated_storage;
	ssize_t		i;

	i = 0;
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	if (!line_buffer[i])
		return (NULL);
	updated_storage = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*updated_storage == '\0')
	{
		free(updated_storage);
		updated_storage = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (updated_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	char		*line;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(storage);
		free(buffer);
		storage = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line(fd, buffer, storage);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	storage = update_line_and_set_storage(line);
	return (line);
}
