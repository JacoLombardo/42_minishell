/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:31:46 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/17 10:58:15 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static t_parser	*parser_init(t_token *token_list, t_data *data)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	parser->err_num = 0;
	parser->curr_token = token_list;
	parser->node = NULL;
	parser->data = data;
	return (parser);
}

void	*set_syntax_error(t_data *data)
{
	data->last_exit = 2;
	ft_putstr_fd("Syntax error\n", 2);
	return (NULL);
}

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] > ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	free_tokens_parser_nodes(t_token *toks, t_parser *prsr, t_node *top)
{
	free_token_list(find_first(toks));
	cleanup_nodes(top);
	free(prsr);
}

t_full_cmd	*parse(char *line, t_data *data)
{
	t_parser	*parser;
	t_node		*top_node;
	t_full_cmd	*output;
	char		*expanded;
	t_token		*token_list;

	expanded = expand_vars(line, data);
	if (ft_strlen(expanded) == 0 || is_empty_line(expanded))
		return (NULL);
	token_list = tokenize(expanded, data);
	free(line);
	free(expanded);
	if (!token_list)
		return (NULL);
	parser = parser_init(token_list, data);
	top_node = make_pipeline(parser);
	if (parser->err_num)
	{
		free_tokens_parser_nodes(token_list, parser, top_node);
		return (set_syntax_error(data));
	}
	output = nodes_to_fullcmd(top_node);
	free_tokens_parser_nodes(token_list, parser, top_node);
	return (output);
}
