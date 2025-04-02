/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:51 by aoger             #+#    #+#             */
/*   Updated: 2025/02/12 19:15:54 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_remove_var(t_env *env, const char *name)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (i < env->size)
	{
		if (ft_strncmp(env->env_array[i], name, len) == 0 \
		&& env->env_array[i][len] == '=')
		{
			free(env->env_array[i]);
			while (i < env->size - 1)
			{
				env->env_array[i] = env->env_array[i + 1];
				i++;
			}
			env->size--;
			env->env_array[env->size] = NULL;
			return (SUCCESS);
		}
		i++;
	}
	return (SUCCESS);
}

int	ft_unset(t_cmd *cmd, t_data *data)
{
	size_t	i;

	if (!cmd->args[1])
		return (SUCCESS);
	i = 1;
	while (cmd->args[i])
	{
		if (ft_is_valid_identifier(cmd->args[i]))
			ft_remove_var(data->env, cmd->args[i]);
		i++;
	}
	return (SUCCESS);
}
