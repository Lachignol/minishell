/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:52:51 by aoger             #+#    #+#             */
/*   Updated: 2025/02/11 23:06:30 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_env(t_env *env)
{
	size_t	i;

	if (!env->env_array)
	{
		printf("Error: Env not init\n");
		return ;
	}
	printf("\nEnvironment Variables:\n");
	printf("Size: %zu\n", env->size);
	i = 0;
	while (i < env->size)
	{
		printf("[%zu]: %s\n", i, env->env_array[i]);
		i++;
	}
}

void	ft_test_init(t_data *data)
{
	printf("\n=== Testing Shell Init ===\n");
	if (!data)
	{
		printf("Error: Data struct is NULL\n");
		return ;
	}
	if (!data->env)
	{
		printf("Error: Env struct is NULL\n");
		return ;
	}
	ft_print_env(data->env);
}
