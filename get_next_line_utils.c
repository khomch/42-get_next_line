/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhomche <akhomche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:02:17 by akhomche          #+#    #+#             */
/*   Updated: 2024/01/22 14:28:12 by akhomche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *src)
{
	size_t		str_length;
	char		*dest;

	str_length = 0;
	while (src[str_length])
		str_length++;
	dest = (char *)malloc(sizeof(char) * (str_length + 1));
	if (dest == ((void *)0))
		return ((void *)0);
	str_length = 0;
	while (src[str_length])
	{
		dest[str_length] = src[str_length];
		str_length++;
	}
	dest[str_length] = '\0';
	return (dest);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_length;

	src_length = 0;
	while (src[src_length] != '\0')
		src_length++;
	if (size > 0)
	{
		while (size > 1 && *src != '\0')
		{
			*dst++ = *src++;
			size--;
		}
		*dst = '\0';
	}
	return (src_length);
}

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	while (*s)
	{
		counter++;
		s++;
	}
	return (counter);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_length;
	size_t	s2_length;
	size_t	total_length;
	char	*s_result;

	if (!s1 || !s2)
		return ((void *)0);
	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	total_length = s1_length + s2_length;
	s_result = (char *)malloc((total_length + 1));
	if (s_result == ((void *)0))
		return ((void *)0);
	ft_strlcpy(s_result, s1, total_length + 1);
	ft_strlcpy(s_result + s1_length, s2, total_length + 1 - s1_length);
	return (s_result);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;

	cc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *)&s[i]);
	return ((void *)0);
}
