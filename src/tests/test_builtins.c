/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:39:35 by aoger             #+#    #+#             */
/*   Updated: 2025/02/26 17:55:50 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_create_mock_cmd(t_cmd *cmd, char **args)
{
	if (!cmd)
		return ;
	cmd->args = args;
	cmd->pipe[0] = -1;
	cmd->pipe[1] = -1;
	cmd->next = NULL;
}

void	ft_test_builtins(t_data *data)
{
	t_cmd	cmd;
	char	*test[4];
	char	*test2[2];
	char	*test3[3];

	(void)data;
	test[0] = "export";
	test[1] = "FOO=42";
	test[2] = "BAR=24";
	test[3] = NULL;
	ft_create_mock_cmd(&cmd, test);
	ft_export(&cmd, data);
	test2[0] = "env";
	test2[1] = NULL;
	ft_create_mock_cmd(&cmd, test2);
	ft_env(&cmd, data);
	test3[0] = "unset";
	test3[1] = "FOO";
	test3[2] = NULL;
	ft_create_mock_cmd(&cmd, test3);
	ft_unset(&cmd, data);
	ft_create_mock_cmd(&cmd, test2);
	ft_env(&cmd, data);
}

/* EXIT Test cases
char *test1[] = {"exit", NULL};					Simple exit
char *test2[] = {"exit", "42", NULL};			Numeric exit
char *test3[] = {"exit", "abc", NULL};			Invalid arg
char *test4[] = {"exit", "42", "foo", NULL};	Too many args
*/
