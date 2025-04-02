/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:08:24 by aoger             #+#    #+#             */
/*   Updated: 2025/02/12 19:00:20 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// env->size doesn't include NULL terminator, so malloc + 2 for new_array
static int	ft_grow_env(t_env *env)
{
	char	**new_array;

	new_array = malloc(sizeof(char *) * (env->size + 2));
	if (!new_array)
		return (ERR_MEMORY);
	ft_memcpy(new_array, env->env_array, sizeof(char *) * (env->size + 1));
	env->size++;
	new_array[env->size] = NULL;
	free(env->env_array);
	env->env_array = new_array;
	return (SUCCESS);
}

// len + 2 for '=' & '\0'
static char	*ft_create_env_str(const char *name, const char *value)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen(name) + ft_strlen(value) + 2;
	new_str = malloc(len);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, name, len);
	ft_strlcat(new_str, "=", len);
	ft_strlcat(new_str, value, len);
	return (new_str);
}

static int	ft_replace_env(t_env *env, const char *name, const char *value, \
size_t i)
{
	char	*new_str;

	new_str = ft_create_env_str(name, value);
	if (!new_str)
		return (EXIT_FAILURE);
	free(env->env_array[i]);
	env->env_array[i] = new_str;
	return (SUCCESS);
}

int	ft_setenv(t_env *env, const char *name, const char *value)
{
	size_t	i;
	size_t	len;
	char	*new_str;

	if (!env || !name || !value)
		return (EXIT_FAILURE);
	len = ft_strlen(name);
	i = 0;
	while (i < env->size)
	{
		if (ft_strncmp(env->env_array[i], name, len) == 0 \
		&& env->env_array[i][len] == '=')
			return (ft_replace_env(env, name, value, i));
		i++;
	}
	if (ft_grow_env(env) != SUCCESS)
		return (EXIT_FAILURE);
	new_str = ft_create_env_str(name, value);
	if (!new_str)
		return (EXIT_FAILURE);
	env->env_array[env->size - 1] = new_str;
	return (SUCCESS);
}

char	*ft_getenv(t_env *env, const char *name)
{
	size_t	i;
	size_t	len;
	char	*value;

	if (!env || !name || !env->env_array)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (i < env->size)
	{
		if (ft_strncmp(env->env_array[i], name, len) == 0 \
		&& env->env_array[i][len] == '=')
		{
			value = env->env_array[i] + len + 1;
			return (value);
		}
		i++;
	}
	return (NULL);
}
