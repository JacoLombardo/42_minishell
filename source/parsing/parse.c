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

static t_parser	*parser_init(t_token *token_list, char **env)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	parser->err_num = 0;
	parser->curr_token = token_list;
	parser->node = NULL;
	parser->env = env;
	return (parser);
}

t_full_cmd	*parse(char *line, char *env[])
{
	t_parser	*parser;
	t_node		*top_node;
	t_full_cmd	*jacopo;
	char		*expanded;
	t_token		*token_list;

	expanded = expand_vars(line, env);
	token_list = tokenize(expanded);
	free(line);
	free(expanded);
	parser = parser_init(token_list, env);
	top_node = make_pipeline(parser);
	jacopo = jacopize(top_node);
	free_token_list(find_first(token_list));
	return (jacopo);
}
