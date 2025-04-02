/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:23 by aoger             #+#    #+#             */
/*   Updated: 2025/02/11 21:31:38 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cd_path(char *path, t_data *data)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (ft_update_pwd(data->env) != SUCCESS)
		return (EXIT_FAILURE);
	return (SUCCESS);
}

static int	ft_cd_home(t_data *data)
{
	char	*path;

	path = ft_getenv(data->env, "HOME");
	if (!path)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (ft_cd_path(path, data) != SUCCESS)
		return (EXIT_FAILURE);
	return (SUCCESS);
}

int	ft_cd(t_cmd *cmd, t_data *data)
{
	if (cmd->args[1] && cmd->args[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!cmd->args[1])
		return (ft_cd_home(data));
	if (ft_cd_path(cmd->args[1], data) != SUCCESS)
		return (EXIT_FAILURE);
	return (SUCCESS);
}
