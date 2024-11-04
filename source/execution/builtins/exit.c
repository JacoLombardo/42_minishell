/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:29:43 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/31 19:51:56 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

void	ft_exit(t_full_cmd *cmd, t_data *data)
{
	ft_free_cmd(cmd);
	ft_free_data_temps(data);
	exit(0);
}
