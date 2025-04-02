/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:42:15 by aoger             #+#    #+#             */
/*   Updated: 2025/03/14 18:25:52 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef ENABLE_BONUS

static void	ft_process_input(char *input, t_data *data)
{
	t_ast	*ast;

	ast = NULL;
	ast = ft_ast_parse_input(input, data);
	if (ast)
	{
		data->exit_status = ft_execute_ast(ast, data);
		ft_free_ast_node(ast);
	}
}
#else

static void	ft_process_input(char *input, t_data *data)
{
	t_cmd	*cmd;
	t_cmd	*first;

	cmd = ft_parse_input(input, data);
	first = cmd;
	if (cmd)
	{
		data->exit_status = ft_execute_cmd(cmd, data, first);
		ft_free_cmd(cmd);
	}
}
#endif

void	ft_shell_loop(t_data *data)
{
	char	*input;

	while (1)
	{
		ft_handle_signal_status(data);
		input = readline(PROMPT);
		ft_handle_signal_status(data);
		if (!input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			return ;
		}
		if (*input)
			data->line_count++;
		add_history(input);
		ft_process_input(input, data);
		free(input);
	}
}
