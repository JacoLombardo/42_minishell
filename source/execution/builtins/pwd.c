/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:28:54 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/30 17:30:31 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_pwd(t_full_cmd *cmd, t_data *data)
{
	char	*cwd;

	(void)cmd;
	cwd = ft_getenv("PWD", data->env);
	printf("%s\n", cwd);
	return (0);
}
