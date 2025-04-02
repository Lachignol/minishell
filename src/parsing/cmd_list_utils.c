/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ascordil <ascordil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:29:07 by ascordil          #+#    #+#             */
/*   Updated: 2025/03/07 15:21:24 by ascordil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_redir(t_redir *redir)
{
	if (!redir)
		return ;
	free(redir->filename);
	free(redir->heredoc_file);
	free(redir->heredoc_delim);
	if (redir->fd != -1)
		close(redir->fd);
	free(redir);
}

t_redir	*ft_init_new_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	ft_bzero(redir, sizeof(t_redir));
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

t_cmd	*ft_init_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;
	cmd->next = NULL;
	return (cmd);
}
