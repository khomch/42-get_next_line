/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhomche <akhomche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:54:35 by akhomche          #+#    #+#             */
/*   Updated: 2024/01/22 14:38:39 by akhomche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	char	*file;
	char	*file1;
	int		fd;
	int		fd1;
	char	*line;
	char	*line1;

	file = "hello.txt";
	file1 = "hello1.txt";
	fd = open(file, O_RDONLY);
	fd1 = open(file1, O_RDONLY);
	if (fd == -1)
	{
		perror("Error while opening file");
		return (1);
	}
	printf("OPEN FILE 1 DESCRIPTOR: %d\n", fd);
	printf("OPEN FILE 2 DESCRIPTOR: %d\n\n\n", fd1);
	line = get_next_line(fd);
	line1 = get_next_line(fd1);
	while (line)
	{
		printf("FIRST FILE: %s\n", line);
		printf("SECOND FILE: %s\n", line1);
		line = get_next_line(fd);
		line1 = get_next_line(fd1);
	}
	printf("FIRST FILE: %s\n", line);
	printf("SECOND FILE: %s\n", line1);
	return (0);
}
