/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:12:10 by aoger             #+#    #+#             */
/*   Updated: 2025/03/04 20:14:04 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_pipes(t_cmd *cmd)
{
	if (cmd->pipe[0] != -1)
		close(cmd->pipe[0]);
	if (cmd->pipe[1] != -1)
		close(cmd->pipe[1]);
}

t_cmd	*ft_find_last_cmd(t_cmd *cmd)
{
	t_cmd	*last_cmd;

	last_cmd = cmd;
	while (last_cmd->next)
		last_cmd = last_cmd->next;
	return (last_cmd);
}
