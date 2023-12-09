/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ax <ax@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 19:02:17 by akhomche          #+#    #+#             */
/*   Updated: 2023/12/09 11:17:23 by ax               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *str, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	while (len--)
	{
		*ptr = 0;
		ptr++;
	}
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
	s = (char *)malloc(sizeof(char) * (len + 1));
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
