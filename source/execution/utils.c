/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:11:21 by jalombar          #+#    #+#             */
/*   Updated: 2024/12/10 13:13:44 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	ft_listlen(t_full_cmd *cmd)
{
	int	len;

	len = 0;
	if (!cmd)
		return (-1);
	while (cmd)
	{
		len++;
		cmd = cmd->next;
	}
	return (len);
}

int	ft_tablen(char **tab)
{
	int	len;

	len = 0;
	if (!tab)
		return (-1);
	while (tab[len])
		len++;
	return (len);
}

int	ft_filelen(char *path)
{
	int		fd;
	int		len;
	char	*line;

	if (!path)
		return (-1);
	fd = open(path, O_RDONLY, 0777);
	if (fd < 0)
		return (-1);
	len = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		len++;
		free(line);
	}
	close(fd);
	return (len);
}

int	ft_event(void)
{
	return (0);
}
