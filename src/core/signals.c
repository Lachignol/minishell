/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:39:34 by aoger             #+#    #+#             */
/*   Updated: 2025/03/14 12:23:37 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	ft_handle_child_signal_status(int status)
{
	int	sig;

	sig = WTERMSIG(status);
	if (sig == SIGSEGV)
		ft_putendl_fd("Segmentation fault (core dumped)", STDERR_FILENO);
	else if (sig == SIGABRT)
		ft_putendl_fd("Aborted (core dumped)", STDERR_FILENO);
	else if (sig == SIGQUIT)
	{
		if (WCOREDUMP(status))
			ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
		else
		{
			ft_putstr_fd("Quit (", STDERR_FILENO);
			ft_putnbr_fd(SIGQUIT, STDERR_FILENO);
			ft_putendl_fd(")", STDERR_FILENO);
		}
	}
	return (ERR_SIGNAL_BASE + sig);
}

static void	ft_handle_sigint(int sig)
{
	g_signum = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_current_cmd_pid == 0)
		rl_redisplay();
}

void	ft_handle_signal_status(t_data *data)
{
	if (g_signum)
	{
		data->exit_status = ERR_SIGNAL_BASE + g_signum;
		g_signum = 0;
	}
}

// SIGINT handles ctrl+C, it means signal interruption
// SIGQUIT handles ctrl+\, SIG_IGN means ignore signal
void	ft_handle_signals(void)
{
	signal(SIGINT, ft_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
