/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:15:00 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/15 11:46:53 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"
# include "structs.h"
# include "types.h"

/* PARSING */
t_full_cmd		*parse(char *line, char *env[]);
t_node		*make_pipeline(t_parser *parser);
t_node		*make_full_command(t_parser *parser);
t_node		*make_redirect(t_redirect *redir_list);
void		append_redirect(t_parser *parser, t_redirect *redir_list);
t_redir_type	get_redirect_type(t_type token_type);
t_node		*make_simple_command(t_parser *parser);

t_redirect	*find_last(t_redirect *redir);
t_node		*create_node(t_node_type type);
void		advance(t_parser *parser);
int			accept(t_parser *parser, t_type type);
int			expect(t_parser *parser, t_type type);
t_type		peek(t_parser *parser);

char	**args_to_array(t_arg *arg_list);
void	redir_to_arrays(t_full_cmd *jacopo, t_redirect *redir_list);
t_full_cmd	*jacopize(t_node *full_cmd);

/* TOKENIZING */
t_token		*tokenize(char *line);
t_token		*new_token(char *value, t_type type);
void		append_token(t_token *token_list, char *value, t_type type);
int			operator_token(t_token *token_list, char *line_pos);
int			value_token(t_token *token_list, char *line_pos);

void	print_ttoken(t_token *token);
int		is_quote(char c);

/* EXPANDING */
int			what_quotes(char const *string);
char		*expand_vars(char *line, char *env[]);

/* UTILS */
t_type		get_type(char *str);
t_token		*find_first(t_token *token_list);
void		free_token_list(t_token *current);
int			what_quotes(char const *string);
int			is_operator_char(char c);

/* TESTING */
void	print_node(t_node *node);
void	print_jacopo(t_full_cmd *jacopo, int index);

#endif
