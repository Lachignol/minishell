/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_pipeline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:09:08 by aoger             #+#    #+#             */
/*   Updated: 2025/03/13 20:47:36 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_cmd_with_args(t_cmd *cmd, t_data *data, t_cmd *first)
{
	int	result;

	result = SUCCESS;
	if (cmd->args && cmd->args[0])
	{
		if (ft_is_builtin(cmd->args[0]))
			result = ft_execute_builtin(cmd, data);
		else
			result = ft_execute_external(cmd, data, first);
	}
	return (result);
}

static int	ft_handle_child(t_cmd *cmd, t_data *data, t_cmd *first)
{
	int	result;

	ft_reset_signals();
	if (ft_open_files(cmd) != SUCCESS || \
	ft_setup_exec_redirections(cmd) != SUCCESS)
	{
		ft_cleanup_shell(data, first);
		exit(EXIT_FAILURE);
	}
	if (cmd->next && !ft_has_output_redir(cmd))
	{
		if (dup2(cmd->pipe[1], STDOUT_FILENO) == -1)
		{
			ft_cleanup_shell(data, first);
			exit(EXIT_FAILURE);
		}
	}
	ft_close_pipes(cmd);
	result = ft_execute_cmd_with_args(cmd, data, first);
	ft_cleanup_shell(data, first);
	exit(result);
}

static int	ft_handle_parent(t_cmd *cmd, t_data *data, t_cmd *first)
{
	int		status;
	pid_t	last_pid;
	int		exit_code;
	t_cmd	*last_cmd;

	exit_code = SUCCESS;
	last_cmd = ft_find_last_cmd(cmd);
	if (cmd->next)
	{
		if (dup2(cmd->pipe[0], STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		return (ft_close_pipes(cmd), ft_exec_pipeline(cmd->next, data, first));
	}
	close(STDIN_FILENO);
	if (waitpid(last_cmd->pid, &status, 0) > 0)
	{
		if (WIFSIGNALED(status))
			exit_code = ft_handle_child_signal_status(status);
		else if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
	}
	last_pid = wait(NULL);
	while (last_pid > 0)
		last_pid = wait(NULL);
	return (g_current_cmd_pid = 0, g_signum = 0, exit_code);
}

static int	ft_handle_empty_cmd_with_redirections(t_cmd *cmd)
{
	cmd->args = malloc(sizeof(char *) * 2);
	if (!cmd->args)
		return (EXIT_FAILURE);
	cmd->args[0] = ft_strdup("cat");
	cmd->args[1] = NULL;
	if (!cmd->args[0])
	{
		free(cmd->args);
		cmd->args = NULL;
		return (EXIT_FAILURE);
	}
	return (SUCCESS);
}

int	ft_exec_pipeline(t_cmd *cmd, t_data *data, t_cmd *first)
{
	pid_t	child_pid;
	int		ret;

	if ((!cmd->args || !cmd->args[0]) && cmd->next && cmd->redirections)
	{
		if (ft_handle_empty_cmd_with_redirections(cmd) != SUCCESS)
			return (EXIT_FAILURE);
	}
	if (cmd->next)
	{
		if (pipe(cmd->pipe) == -1)
			return (EXIT_FAILURE);
	}
	child_pid = fork();
	if (child_pid == -1)
		return (EXIT_FAILURE);
	g_current_cmd_pid = child_pid;
	if (child_pid == 0)
		ft_handle_child(cmd, data, first);
	cmd->pid = child_pid;
	ret = ft_handle_parent(cmd, data, first);
	return (ret);
}
