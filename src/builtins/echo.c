/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:05 by aoger             #+#    #+#             */
/*   Updated: 2025/02/25 14:02:30 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Also works with multiple n like "-nnn"
static int	ft_is_n_flag(char *str)
{
	size_t	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// Apparently, shell needs exit status so return (SUCCESS)
int	ft_echo(t_cmd *cmd)
{
	size_t	i;
	int		n_flag;

	if (!cmd->args[1])
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (SUCCESS);
	}
	i = 1;
	n_flag = 0;
	while (cmd->args[i] && ft_is_n_flag(cmd->args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS);
}
