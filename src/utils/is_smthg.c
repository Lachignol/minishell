/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_smthg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:06:09 by aoger             #+#    #+#             */
/*   Updated: 2025/03/05 15:53:03 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || \
			!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") || \
			!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") || \
			!ft_strcmp(cmd, "exit"));
}

int	ft_is_valid_identifier(char *str)
{
	size_t	i;

	if (!str || str[0] == '\0' || ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_shell_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int	ft_is_numeric(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
