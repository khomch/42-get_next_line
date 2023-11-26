/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ax <ax@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:02:17 by akhomche          #+#    #+#             */
/*   Updated: 2023/11/23 14:33:07 by ax               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>


void	*ft_memset(void *str, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (len--)
	{
		*ptr = c;
		ptr++;
	}
	return (str);
}

void	ft_bzero(void *str, size_t len)
{
	ft_memset(str, 0, len);
}

void	*ft_calloc(size_t num, size_t size)
{
	void	*ptr;

	if (num && size && (num > UINT_MAX / size))
		return (NULL);
	ptr = malloc(num * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, num * size);
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	len;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + (ft_strlen(s2));
	s = ft_calloc(len + 1, sizeof(char));
	if (!s)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		s[len] = s1[len];
		len++;
	}
	i = 0;
	while (s2[i])
	{
		s[len + i] = s2[i];
		i++;
	}
	return (s);
}

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

static int	is_in_set(char const *set, char c)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	l;
	size_t	r;
	size_t	i;

	if (!s1)
		return (NULL);
	r = ft_strlen(s1);
	l = 0;
	while (l < r && is_in_set(set, s1[l]))
		l++;
	while (r > l && is_in_set(set, s1[r - 1]))
		r--;
	res = (char *)malloc(sizeof(char) * (r - l + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (l < r)
		res[i++] = s1[l++];
	res[i] = '\0';
	return (res);
}

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;
	char			*res;

	res = NULL;
	cc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			res = ((char *)&s[i]);
		i++;
	}
	if (s[i] == cc)
		res = ((char *)&s[i]);
	return (res);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}


char	start[5];

void	write_start(char *current, char *start, int	j)
{
	int	len;
	int	x;

	x = 0;
	len = ft_strlen(current);
	while(j > 0)
	{
		start[x] = current[len - j];
		x++;
		j--;
	}
	start[x] = '\0';
}

void	add_start_to_buffer(char *start, char *buffer)
{
	if (ft_strlen(start) > 0)
	{
		ft_strlcat(buffer, start, sizeof(buffer));
		ft_bzero(start, sizeof(start));
	}
}


void	get_next_line(int fd)
{
	int		bytesRead;
	char	buffer[1024] = "";
	char	current[5];
	int		i;
	int		j;

	while ((bytesRead = read(fd, current, 4)) > 0)
	{
		current[bytesRead] = '\0';
		add_start_to_buffer(start, buffer);
		ft_strlcat(buffer, current, sizeof(buffer));
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
			ft_bzero(buffer, sizeof(buffer));
			break ;
		}
	}
}

int	main(void)
{
	char	*filePtr;

	int		fd;

	filePtr = "hello.txt";
	fd = open(filePtr, O_RDWR);
	if (fd == -1)
	{
		printf("Error while open file\n");
		exit(1);
	}
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);

	// bytesRead = read(fd, buffer, 4);
    // printf("%d bytes read!\n", bytesRead);
	// printf("%s", buffer);
	close(fd);
	return (0);
}
