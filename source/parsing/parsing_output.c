/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:32:17 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/30 16:34:07 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static char	**args_to_array(t_arg *arg_list)
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
	result = malloc(sizeof(char *) * (arg_count + 2));
	arg_count = 1;
	while (first->next)
	{
		first = first->next;
		result[arg_count] = super_trimmer(first->value);
		arg_count++;
	}
	result[arg_count] = NULL;
	return (result);
}

static void	redir_to_arrays(t_full_cmd *jacopo, t_redirect *redir_list)
{
	t_redirect	*first;
	int			count;

	count = 0;
	first = redir_list;
	while (redir_list->next)
	{
		count++;
		redir_list = redir_list->next;
	}
	if (count)
	{
		jacopo->redirections = malloc(sizeof(t_redir_type) * count);
		jacopo->targets = malloc(sizeof(char *) * (count + 1));
		count = 0;
		while (first->next)
		{
			first = first->next;
			jacopo->redirections[count] = first->type;
			jacopo->targets[count] = super_trimmer(first->target);
			count++;
		}
		jacopo->targets[count] = NULL;
	}
}

static void	fill_full_cmd(t_full_cmd *jacopo, t_node *full_cmd)
{
	jacopo->cmd = NULL;
	jacopo->args = NULL;
	jacopo->redirections = NULL;
	jacopo->targets = NULL;
	jacopo->operator = NULL;
	if (full_cmd->pair->left)
	{
		jacopo->cmd = ft_strdup(full_cmd->pair->left->simp_cmd->command);
		jacopo->args = args_to_array(full_cmd->pair->left->simp_cmd->arg);
		jacopo->args[0] = ft_strdup(jacopo->cmd);
	}
	jacopo->built_in = is_builtin(jacopo->cmd);
	redir_to_arrays(jacopo, full_cmd->pair->right->redirect);
}

t_full_cmd	*nodes_to_fullcmd(t_node *pipeline)
{
	t_full_cmd	*jacopo;
	t_node		*full_cmd;
	static int	index;

	if (!pipeline)
		return (NULL);
	jacopo = malloc(sizeof(t_full_cmd));
	if (!jacopo)
		return (NULL);
	full_cmd = pipeline->pair->left;
	jacopo->index = index;
	fill_full_cmd(jacopo, full_cmd);
	index++;
	jacopo->next = nodes_to_fullcmd(pipeline->pair->right);
	if (jacopo->next)
		jacopo->operator = ft_strdup("|");
	else
		jacopo->operator = NULL;
	index = 0;
	return (jacopo);
}
