/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 21:03:38 by aoger             #+#    #+#             */
/*   Updated: 2025/02/11 21:03:53 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_pwd(t_env *env)
{
	char	*pwd;
	char	*old_pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (EXIT_FAILURE);
	old_pwd = ft_getenv(env, "PWD");
	if (old_pwd)
		ft_setenv(env, "OLDPWD", pwd);
	ft_setenv(env, "PWD", pwd);
	free(pwd);
	return (SUCCESS);
}
