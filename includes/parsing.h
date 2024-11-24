/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:15:00 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/06 15:47:35 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"
# include "structs.h"
# include "types.h"

/* PARSING */
t_full_cmd		*parse(char *line, t_data *data);
t_node			*make_pipeline(t_parser *parser);
t_node			*make_full_command(t_parser *parser);
t_node			*make_redirect(t_redirect *redir_list);
void			append_redirect(t_parser *parser, t_redirect *redir_list);
t_redir_type	get_redirect_type(t_type token_type);
t_node			*make_simple_command(t_parser *parser, t_redirect *redir_list);

t_redirect		*find_last(t_redirect *redir);
t_arg			*find_last_arg(t_arg *arg);
t_node			*create_node(t_node_type type);
void			advance(t_parser *parser);
int				accept(t_parser *parser, t_type type);
int				accept_redirect(t_parser *parser);
int				expect(t_parser *parser, t_type type);
t_type			peek(t_parser *parser);

t_full_cmd		*nodes_to_fullcmd(t_node *full_cmd);
int				is_builtin(char *cmd);
int				is_assignment(char *input);
void			*set_syntax_error(t_data *data);

/* TOKENIZING */
t_token			*tokenize(char *line, t_data *data);
t_token			*new_token(char *value, t_type type);
void			append_token(t_token *token_list, char *value, t_type type);
int				operator_token(t_token *token_list, char *line_pos);
int				value_token(t_token *token_list, char *line_pos);

/* QUOTE HANDLING */
int				what_quotes(char const *string);
char			*trim_quote(char *str);
char			*super_trimmer(char *line);
int				is_quote(char c);

/* EXPANDING */
char			*expand_vars(char *line, t_data *data);
int				is_bash_valid(char c);
char			*append_value(char *new_line, char *var_value, char *var_name);
char			*append_char(char *new_line, char c);
char			*ft_better_strnstr(const char *big, const char *little,
					size_t len);
/* SHELL VARIABLES */
void			ft_var_to_temp(char *var, t_data *data);
char			*ft_temp_to_env(char *var, t_data *data);
char			**copy_and_enhance_env(t_data *data);

/* UTILS */
t_type			get_type(char *str);
t_token			*find_first(t_token *token_list);
void			free_token_list(t_token *current);
int				what_quotes(char const *string);
int				is_operator_char(char c);

/* CLEANUP */
void			cleanup_nodes(t_node *top_node);

#endif
