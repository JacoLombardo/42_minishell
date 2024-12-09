/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:28:54 by jalombar          #+#    #+#             */
/*   Updated: 2024/12/02 09:46:20 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

char	*trim_trailing_slash(char *path)
{
	char	*trimmed;
	size_t	i;

	if (path[ft_strlen(path) - 1] != '/' || ft_strlen(path) == 1)
		trimmed = ft_strdup(path);
	else
	{
		trimmed = malloc(sizeof(char) * (ft_strlen(path)));
		if (!trimmed)
			return (NULL);
		i = 0;
		while (i < ft_strlen(path) - 1)
		{
			trimmed[i] = path[i];
			i++;
		}
		trimmed[i] = '\0';
	}
	free (path);
	return (trimmed);
}

int	ft_pwd(t_full_cmd *cmd, t_data *data)
{
	char	*cwd;

	(void)cmd;
	cwd = ft_getenv("PWD", data->env);
	printf("%s\n", cwd);
	return (0);
}
