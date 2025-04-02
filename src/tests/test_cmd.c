/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:22:48 by aoger             #+#    #+#             */
/*   Updated: 2025/03/06 23:20:07 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*ft_create_cmd(char **args)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = args;
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*ft_test_execution(void)
{
	t_cmd	*first;
	t_cmd	*second;
	char	**args1;
	char	**args2;

	args1 = malloc(sizeof(char *) * 3);
	args2 = malloc(sizeof(char *) * 3);
	if (!args1 || !args2)
		return (NULL);
	args1[0] = ft_strdup("ls");
	args1[1] = ft_strdup("-l");
	args1[2] = NULL;
	args2[0] = ft_strdup("grep");
	args2[1] = ft_strdup("include");
	args2[2] = NULL;
	first = ft_create_cmd(args1);
	second = ft_create_cmd(args2);
	if (!first || !second)
		return (NULL);
	first->next = second;
	return (first);
}

void	ft_test_cmd(t_data *data)
{
	t_cmd	*cmd;

	cmd = ft_test_execution();
	if (cmd)
	{
		data->exit_status = ft_execute_cmd(cmd, data, cmd);
		ft_free_cmd(cmd);
	}
}
