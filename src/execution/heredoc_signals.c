/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:55:58 by aoger             #+#    #+#             */
/*   Updated: 2025/03/04 12:56:22 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_heredoc_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

int	ft_setup_heredoc_signals(void)
{
	signal(SIGINT, ft_handle_heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (SUCCESS);
}
