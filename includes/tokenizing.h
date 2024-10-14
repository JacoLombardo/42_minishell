/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:17:11 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/14 19:18:13 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZING_H
# define TOKENIZING_H

# include "../minishell.h"

typedef struct	s_token {
	t_type			type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

t_token		*tokenize(char *line);
t_token		*new_token(char *value, t_type type);
void		append_token(t_token *token_list, char *value, t_type type);
int			operator_token(t_token *token_list, char *line_pos);
int			value_token(t_token *token_list, char *line_pos);

#endif