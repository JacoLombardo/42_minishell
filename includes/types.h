/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:50:02 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/21 13:58:54 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "structs.h"

typedef enum e_op_type
{
	R_PIPE,
	R_AND,
	R_OR,
}	t_op_type;

typedef enum e_redir_type
{
	R_APPEND,
	R_HEREDOC,
	R_OUT,
	R_IN,
	R_ERR,
}	t_redir_type;

/* PARSING */
typedef enum e_type
{
	T_ERR,
	T_THING,
	T_PIPE,
	T_OR,
	T_AND,
	T_APPEND,  // >>
	T_HEREDOC, // <<
	T_OUT,
	T_IN,
}	t_type;

typedef enum e_node_type
{
	PIPELINE,
	FULL_CMD,
	REDIRECT,
	SIMPLE_CMD,
}	t_node_type;

#endif
