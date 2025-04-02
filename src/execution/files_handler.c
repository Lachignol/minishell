/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 23:17:40 by aoger             #+#    #+#             */
/*   Updated: 2025/03/14 00:10:07 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_files(t_cmd *cmd)
{
	if (cmd->redirections->fd != STDIN_FILENO)
		close(cmd->redirections->fd);
	if (cmd->redirections->fd != STDOUT_FILENO)
		close(cmd->redirections->fd);
}

#ifdef ENABLE_BONUS

static int	ft_open_file(t_redir *redir)
{
	if (!redir->filename)
		return (EXIT_FAILURE);
	if (ft_handle_redirection_wildcards(redir) != SUCCESS)
		return (EXIT_FAILURE);
	if (redir->type == TOKEN_REDIR_OUT)
		redir->fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == TOKEN_APPEND)
		redir->fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == TOKEN_REDIR_IN)
		redir->fd = open(redir->filename, O_RDONLY);
	if (redir->fd == -1)
	{
		if (redir->type == TOKEN_REDIR_IN)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(redir->filename, STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		}
		return (EXIT_FAILURE);
	}
	return (SUCCESS);
}
#else

static int	ft_open_file(t_redir *redir)
{
	if (!redir->filename)
		return (EXIT_FAILURE);
	if (redir->type == TOKEN_REDIR_OUT)
		redir->fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == TOKEN_APPEND)
		redir->fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == TOKEN_REDIR_IN)
		redir->fd = open(redir->filename, O_RDONLY);
	if (redir->fd == -1)
	{
		if (redir->type == TOKEN_REDIR_IN)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(redir->filename, STDERR_FILENO);
			ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		}
		return (EXIT_FAILURE);
	}
	return (SUCCESS);
}
#endif

int	ft_open_files(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			if (redir->fd == -1 && redir->heredoc_file)
			{
				redir->fd = open(redir->heredoc_file, O_RDONLY);
				if (redir->fd == -1)
					return (EXIT_FAILURE);
			}
		}
		else if (ft_open_file(redir) != SUCCESS)
			return (EXIT_FAILURE);
		redir = redir->next;
	}
	return (SUCCESS);
}
