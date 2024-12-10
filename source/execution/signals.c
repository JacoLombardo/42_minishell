/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:25:29 by jalombar          #+#    #+#             */
/*   Updated: 2024/12/10 11:09:57 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	ft_handle_sigint(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	rl_cleanup_after_signal();
}

void	ft_handle_sigint_heredoc(int signal)
{
	(void)signal;
	g_flag = 130;
	rl_done = 1;
}

void	ft_handle_sigint_bin(int signal)
{
	(void) signal;
	ft_putstr_fd("\n", 1);
}

void	ft_handle_sigquit(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	ft_sig_init(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
