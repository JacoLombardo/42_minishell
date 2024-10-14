/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:32:17 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/14 19:32:19 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	**args_to_array(t_arg *arg_list)
{
	char	**result;
	int		arg_count;
	t_arg	*first;

	arg_count = 0;
	first = arg_list;
	while (arg_list->next)
	{
		arg_count++;
		arg_list = arg_list->next;
	}
	result = malloc(sizeof(char*) * (arg_count + 2));
	arg_count = 1;
	while (first->next)
	{
		first = first->next;
		result[arg_count] = ft_strdup(first->value);
		arg_count++;
	}
	result[arg_count] = NULL;
	return (result);
}

void	redir_to_arrays(t_cmd *jacopo, t_redirect *redir_list)
{
	t_redirect		*first;
	int				count;

	count = 0;
	first = redir_list;
	while (redir_list->next)
	{
		count++;
		redir_list = redir_list->next;
	}
	jacopo->redir_types = malloc(sizeof(t_redir_type) * count);
	jacopo->targets = malloc(sizeof(char*) * (count + 1));
	count = 0;
	while (first->next)
	{
		first = first->next;
		jacopo->redir_types[count] = first->type;
		jacopo->targets[count] = ft_strdup(first->target);
		count++;
	}
	jacopo->targets[count] = NULL;
}

t_cmd	*jacopize(t_node *full_cmd)
{
	t_cmd	*jacopo;

	jacopo = malloc(sizeof(t_cmd));
	if (!jacopo)
		return (NULL);
	jacopo->cmd = ft_strdup(full_cmd->pair->left->cmd->command);
	jacopo->args = args_to_array(full_cmd->pair->left->cmd->arg);
	jacopo->args[0] = ft_strdup(jacopo->cmd);
	jacopo->redir_types = NULL;
	jacopo->targets = NULL;
	redir_to_arrays(jacopo, full_cmd->pair->right->redirect);
	
	return (jacopo);
}
