/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:14:12 by csilva-r          #+#    #+#             */
/*   Updated: 2024/05/28 10:14:14 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_to_line(int fd, char *line)
{
	char	*buff;
	int		bytes_read;
	char	*temp;

	buff = malloc((sizeof(char) * BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(line, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buff);
			free(line);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		temp = line;
		line = ft_strjoin(temp, buff);
		free(temp);
	}
	free (buff);
	return (line);
}

static char	*set_line_and_remember(char *line)
{
	size_t	i;
	char	*remembrance;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	remembrance = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (i == ft_strlen(line))
	{
		free(remembrance);
		remembrance = NULL;
	}
	if (line[i] != '\0')
		line[i + 1] = '\0';
	return (remembrance);
}

char	*get_next_line(int fd)
{
	static char	*remembrance[MAX_ITEMS];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (remembrance[fd])
		{
			free(remembrance[fd]);
			remembrance[fd] = NULL;
		}
		return (NULL);
	}
	if (!remembrance[fd])
		remembrance[fd] = ft_strdup("");
	line = read_to_line(fd, remembrance[fd]);
	remembrance[fd] = NULL;
	if (!line || ft_strlen(line) < 1)
	{
		free(line);
		return (NULL);
	}
	remembrance[fd] = set_line_and_remember(line);
	return (line);
}
