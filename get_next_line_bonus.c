/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dperez-a <dperez-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 09:38:04 by dani_mm__         #+#    #+#             */
/*   Updated: 2024/01/31 14:13:05 by dperez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *buff)
{
	char	*str;
	int		rd_bytes;

	str = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!str)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(buff, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, str, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(str);
			free(buff);
			return (NULL);
		}
		str[rd_bytes] = '\0';
		buff = ft_strjoin(buff, str);
	}
	free(str);
	return (buff);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buff[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buff[fd] = ft_read(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	line = ft_get_line(buff[fd]);
	buff[fd] = ft_new(buff[fd]);
	return (line);
}

/*int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("tests/test.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}*/
