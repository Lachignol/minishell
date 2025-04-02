/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:35:02 by aoger             #+#    #+#             */
/*   Updated: 2025/02/12 18:00:27 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// We need to handle cases like "env ls -l"
// which executes "ls -l" and not "env"
int	ft_env(t_cmd *cmd, t_data *data)
{
	size_t	i;

	if (!cmd->args[1])
	{
		i = 0;
		while (i < data->env->size)
		{
			ft_putendl_fd(data->env->env_array[i], STDOUT_FILENO);
			i++;
		}
		return (EXIT_SUCCESS);
	}
	ft_putstr_fd("env: '", STDERR_FILENO);
	ft_putstr_fd(cmd->args[1], STDERR_FILENO);
	ft_putendl_fd("': No such file or directory", STDERR_FILENO);
	return (ERR_CMD_NOT_FOUND);
}
