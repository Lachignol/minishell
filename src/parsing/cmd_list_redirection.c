/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:29:07 by ascordil          #+#    #+#             */
/*   Updated: 2025/03/14 00:48:35 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_add_redir_to_cmd_redir_list(t_cmd *cmd, t_redir *new)
{
	t_redir	*last;

	if (!cmd->redirections)
		cmd->redirections = new;
	else
	{
		last = cmd->redirections;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

static t_redir	*ft_setup_redirection(t_token *token, t_data *data)
{
	t_redir	*new;

	new = ft_init_new_redir();
	if (!new)
		return (NULL);
	new->type = token->type;
	if (new->type == TOKEN_HEREDOC)
	{
		new->heredoc_delim = ft_strdup(token->next->content);
		if (!new->heredoc_delim)
			return (ft_free_redir(new), NULL);
		new->heredoc_start_line = data->line_count;
	}
	else
	{
		new->filename = ft_strdup(token->next->content);
		if (!new->filename)
			return (ft_free_redir(new), NULL);
	}
	return (new);
}

int	ft_process_redirection(t_cmd *cmd, t_token *token, t_data *data)
{
	t_redir	*new;

	if (!token->next || token->next->type != TOKEN_WORD)
		return (EXIT_FAILURE);
	new = ft_setup_redirection(token, data);
	if (!new)
		return (EXIT_FAILURE);
	ft_add_redir_to_cmd_redir_list(cmd, new);
	return (SUCCESS);
}
