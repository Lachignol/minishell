/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_structs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:20:12 by aoger             #+#    #+#             */
/*   Updated: 2025/03/15 00:48:36 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_token(t_token *token)
{
	free(token->content);
	free(token->quote_types);
	free(token);
}

void	ft_free_heredoc_redir_list(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = redir;
	while (current)
	{
		next = current->next;
		if (current->filename)
			free(current->filename);
		if (current->heredoc_file)
			free(current->heredoc_file);
		if (current->heredoc_delim)
			free(current->heredoc_delim);
		if (current->fd != -1)
			close(current->fd);
		free(current);
		current = next;
	}
}

void	ft_free_redir_list(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = redir;
	while (current)
	{
		next = current->next;
		if (current->filename)
			free(current->filename);
		if (current->heredoc_file)
		{
			if (access(current->heredoc_file, F_OK) == 0)
				unlink(current->heredoc_file);
			free(current->heredoc_file);
		}
		if (current->heredoc_delim)
			free(current->heredoc_delim);
		if (current->fd != -1)
			close(current->fd);
		free(current);
		current = next;
	}
}

void	ft_free_token_list(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->content)
			free(current->content);
		if (current->quote_types)
			free(current->quote_types);
		free(current);
		current = next;
	}
}

void	ft_free_cmd(t_cmd *cmd)
{
	t_cmd	*next;

	while (cmd)
	{
		next = cmd->next;
		if (cmd->args)
			ft_free_array(cmd->args);
		ft_free_redir_list(cmd->redirections);
		ft_close_pipes(cmd);
		free(cmd);
		cmd = next;
	}
}
