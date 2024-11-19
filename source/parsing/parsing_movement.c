/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:32:06 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/14 19:32:08 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	advance(t_parser *parser)
{
	parser->curr_token = parser->curr_token->next;
}

int	accept(t_parser *parser, t_type type)
{
	if (parser->curr_token->next && parser->curr_token->next->type == type)
	{
		advance(parser);
		return (TRUE);
	}
	return (FALSE);
}

int	expect(t_parser *parser, t_type type)
{
	if (accept(parser, type))
		return (TRUE);
	parser->err_num = 1;
	return (FALSE);
}
/* todo: cleanup after failing here? */

t_type	peek(t_parser *parser)
{
	if (parser->curr_token)
		return (parser->curr_token->type);
	return (T_ERR);
}
