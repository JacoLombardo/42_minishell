/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:27:15 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/17 10:27:16 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_node(t_node *node)
{
	t_arg		*arg;
	t_redirect	*redir;
	const char	*types[] = {"APPEND", "HEREDOC", "OUT", "IN", "ERROR"};

	if (!node)
	{
		printf("\n\t(empty)");
		return ;
	}
	if (node->type == PIPELINE)
	{
		printf("\npipeline: ");
		printf("\nleft: ");
		print_node(node->pair->left);
		printf("\nright: ");
		print_node(node->pair->right);
	}
	else if (node->type == FULL_CMD)
	{
		printf("\n\tfull command: ");
		print_node(node->pair->left);
		print_node(node->pair->right);
	}
	else if (node->type == REDIRECT)
	{
		printf("\n\t\tredirects: ");
		redir = node->redirect;
		while (redir->next)
		{
			redir = redir->next;
			printf("%s (target %s), ", types[redir->type], redir->target);
		}
	}
	else if (node->type == SIMPLE_CMD)
	{
		printf("\n\t\tsimple_command: ");
		printf("cmd %s, args: ", node->simp_cmd->command);
		arg = node->simp_cmd->arg;
		while (arg->next)
		{
			arg = arg->next;
			printf("%s, ", arg->value);
		}
	}
	else
		printf("?");
	printf("\n");
}

void	print_jacopo(t_full_cmd *jacopo, int index)
{
	const char	*types[] = {"APPEND", "HEREDOC", "OUT", "IN", "ERROR"};
	int			i;
	int			j;

	printf("command %i\n", index);
	printf("jacopo's command: %s\n", jacopo->cmd);
	printf("jacopo's args: ");
	i = 0;
	while (jacopo->args[i])
	{
		printf("%s, ", jacopo->args[i]);
		i++;
	}
	printf("\n");
	printf("jacopo's targets: ");
	i = 0;
	while (jacopo->targets[i])
	{
		printf("%s, ", jacopo->targets[i]);
		i++;
	}
	printf("\n");
	printf("jacopo's redirection types: ");
	j = i;
	while (i > 0)
	{
		printf("%s, ", types[jacopo->redirections[j - i]]);
		i--;
	}
	printf("\n");
	printf("jacopo's operator: %s", jacopo->operator);
	printf("\n");
	if (jacopo->next)
	{
		print_jacopo(jacopo->next, index + 1);
	}
}
