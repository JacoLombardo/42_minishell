/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:31:46 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/15 11:45:26 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_parser	*parser_init(t_token *token_list)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	parser->err_num = 0;
	parser->curr_token = token_list;
	parser->node = NULL;
	return (parser);
}

/*	Jacopo:
	For now, you can call this function to return a t_cmd like we discussed.
	The struct is also signalled with comments in the header, check it out.
	"print_jacopo" prints it.
	None of this is taking pipelines into account, but this works for commands
	+ args + any number of redirections.
	Let me know how it goes.
*/
t_full_cmd	*parse(char *line, char *env[])
{
	t_parser	*parser;
	t_node		*top_node;
	t_full_cmd		*jacopo;
	char		*expanded;
	t_token		*token_list;

	expanded = expand_vars(line, env);
	token_list = tokenize(expanded);
	free(line);
	free(expanded);
	parser = parser_init(token_list);
	top_node = make_pipeline(parser);
	print_node(top_node);
	jacopo = jacopize(top_node);
	//jacopo = NULL;
	free_token_list(find_first(token_list));
	return(jacopo);
}
