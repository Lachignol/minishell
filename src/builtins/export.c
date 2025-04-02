/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:34:43 by aoger             #+#    #+#             */
/*   Updated: 2025/02/28 15:32:58 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_process_var(char *arg, t_env *env)
{
	char	*equal_sign;
	char	*value;
	char	*tmp_arg;

	tmp_arg = ft_strdup(arg);
	if (!tmp_arg)
		return (EXIT_FAILURE);
	equal_sign = ft_strchr(tmp_arg, '=');
	if (equal_sign)
	{
		*equal_sign = '\0';
		value = equal_sign + 1;
	}
	else
		value = "";
	if (!ft_is_valid_identifier(tmp_arg))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (free(tmp_arg), EXIT_FAILURE);
	}
	if (ft_setenv(env, tmp_arg, value) != SUCCESS)
		return (free(tmp_arg), EXIT_FAILURE);
	return (free(tmp_arg), SUCCESS);
}

static int	ft_print_sorted_env(t_env *env)
{
	size_t	i;
	char	**sorted;

	sorted = ft_copy_str_array(env->env_array, env->size);
	if (!sorted)
		return (ERR_MEMORY);
	ft_sort_str_array(sorted, env->size);
	i = 0;
	while (i < env->size)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(sorted[i], STDOUT_FILENO);
		i++;
	}
	free(sorted);
	return (SUCCESS);
}

int	ft_export(t_cmd *cmd, t_data *data)
{
	size_t	i;

	if (!cmd->args[1])
		return (ft_print_sorted_env(data->env));
	i = 1;
	while (cmd->args[i])
	{
		if (ft_process_var(cmd->args[i], data->env) != SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	return (SUCCESS);
}
