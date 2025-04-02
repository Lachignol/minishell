/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:13:30 by aoger             #+#    #+#             */
/*   Updated: 2025/03/14 00:43:47 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_copy_env(t_env *env, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		env->env_array[i] = ft_strdup(envp[i]);
		if (!env->env_array[i])
		{
			while (i > 0)
				free(env->env_array[--i]);
			return (ERR_MEMORY);
		}
		i++;
	}
	env->env_array[i] = NULL;
	return (SUCCESS);
}

static size_t	ft_env_size(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

// envp is read_only
// shell needs to mofify environment (export/unset)
// so we need to maintain own copy
static int	ft_init_env(t_data *data, char **envp)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (ERR_MEMORY);
	env->size = ft_env_size(envp);
	env->env_array = malloc(sizeof(char *) * (env->size + 1));
	if (!env->env_array)
	{
		free(env);
		return (ERR_MEMORY);
	}
	if (ft_copy_env(env, envp) != SUCCESS)
	{
		free(env->env_array);
		free(env);
		return (ERR_MEMORY);
	}
	data->env = env;
	return (SUCCESS);
}

static void	ft_init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
}

int	ft_init_shell(t_data *data, char **envp)
{
	ft_init_data(data);
	if (ft_init_env(data, envp) != SUCCESS)
		return (ERR_MEMORY);
	return (SUCCESS);
}
