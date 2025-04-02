/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:20:23 by aoger             #+#    #+#             */
/*   Updated: 2025/03/10 00:24:54 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_env(t_env *env)
{
	size_t	i;

	if (!env)
		return ;
	if (env->env_array)
	{
		i = 0;
		while (i < env->size)
		{
			free(env->env_array[i]);
			i++;
		}
		free(env->env_array);
	}
	free(env);
}

void	ft_cleanup_heredoc_shell(t_data *data, t_cmd *cmd)
{
	t_cmd	*next;

	if (data)
	{
		if (data->env)
		{
			ft_free_env(data->env);
			data->env = NULL;
		}
	}
	while (cmd)
	{
		next = cmd->next;
		if (cmd->args)
			ft_free_array(cmd->args);
		ft_free_heredoc_redir_list(cmd->redirections);
		ft_close_pipes(cmd);
		free(cmd);
		cmd = next;
	}
	rl_clear_history();
}

void	ft_cleanup_shell(t_data *data, t_cmd *cmd)
{
	if (data)
	{
		if (data->env)
		{
			ft_free_env(data->env);
			data->env = NULL;
		}
	}
	if (cmd)
		ft_free_cmd(cmd);
	rl_clear_history();
}
