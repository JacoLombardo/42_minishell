/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:32:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/17 10:27:00 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	print_ttoken(t_token *token)
{
	printf("value: %s\ttype: %i. ", token->value, token->type);
	if (!token->next)
		printf("this is the last one");
	printf("\n");
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (TRUE);
	return (FALSE);
}

t_type	get_type(char *str)
{
	if (ft_strncmp(str, "||", 2) == 0)
		return (T_OR);
	else if (ft_strncmp(str, "&&", 2) == 0)
		return (T_AND);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (T_APPEND);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (T_HEREDOC);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (T_PIPE);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (T_OUT);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (T_IN);
	return (T_THING);
}

int	what_quotes(char const *string)
{
	int	i;
	int	quote_type;

	i = 0;
	quote_type = 0;
	while (string[i])
	{
		if (string[i] == '\"' && quote_type == 0)
			quote_type = 1;
		else if (string[i] == '\"' && quote_type == 1)
			quote_type = 0;
		else if (string[i] == '\'' && quote_type == 0)
			quote_type = 2;
		else if (string[i] == '\'' && quote_type == 2)
			quote_type = 0;
		i++;
	}
	return (quote_type);
}

t_token	*find_first(t_token *token_list)
{
	while (token_list->prev != NULL)
		token_list = token_list->prev;
	return (token_list);
}

void	free_token_list(t_token *current)
{
	t_token	*next;

	next = current;
	while (next)
	{
		free(current->value);
		next = current->next;
		free(current);
		current = next;
	}
}
