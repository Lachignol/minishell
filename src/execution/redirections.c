/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:22:07 by aoger             #+#    #+#             */
/*   Updated: 2025/03/10 01:03:20 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_has_output_redir(t_cmd *cmd)
{
	t_redir	*redir;
	int		has_output_redir;

	has_output_redir = 0;
	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_APPEND)
		{
			has_output_redir = 1;
			break ;
		}
		redir = redir->next;
	}
	return (has_output_redir);
}

static t_redir	*ft_get_last_output(t_cmd *cmd)
{
	t_redir	*last;
	t_redir	*current;

	last = NULL;
	current = cmd->redirections;
	while (current)
	{
		if (current->type == TOKEN_REDIR_OUT || current->type == TOKEN_APPEND)
			last = current;
		current = current->next;
	}
	return (last);
}

static t_redir	*ft_get_last_input(t_cmd *cmd)
{
	t_redir	*last;
	t_redir	*current;

	last = NULL;
	current = cmd->redirections;
	while (current)
	{
		if (current->type == TOKEN_REDIR_IN || current->type == TOKEN_HEREDOC)
			last = current;
		current = current->next;
	}
	return (last);
}

int	ft_setup_exec_redirections(t_cmd *cmd)
{
	t_redir	*last_in;
	t_redir	*last_out;

	last_in = ft_get_last_input(cmd);
	last_out = ft_get_last_output(cmd);
	if (last_in)
	{
		if (dup2(last_in->fd, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	if (last_out)
	{
		if (dup2(last_out->fd, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	return (SUCCESS);
}
