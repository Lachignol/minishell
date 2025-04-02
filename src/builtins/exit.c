/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:35:11 by aoger             #+#    #+#             */
/*   Updated: 2025/03/13 03:47:53 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// data->exit_status, if no args we use last status
int	ft_exit(t_cmd *cmd, t_data *data)
{
	int	status;

	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (!cmd->args[1])
	{
		ft_cleanup_shell(data, cmd);
		exit(data->exit_status);
	}
	if (!ft_is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		ft_cleanup_shell(data, cmd);
		exit(255);
	}
	if (cmd->args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	status = ft_normalize_status(ft_atoi(cmd->args[1]));
	ft_cleanup_shell(data, cmd);
	exit(status);
}
