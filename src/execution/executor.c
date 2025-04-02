/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:03:54 by aoger             #+#    #+#             */
/*   Updated: 2025/03/13 20:47:51 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	g_current_cmd_pid = 0;
	if (WIFSIGNALED(status))
		return (ft_handle_child_signal_status(status));
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}

int	ft_execute_external(t_cmd *cmd, t_data *data, t_cmd *first)
{
	char	*path;
	pid_t	pid;

	path = ft_find_command(cmd->args[0], data->env);
	if (!path)
		return (ft_print_null_path_error(cmd), ERR_CMD_NOT_FOUND);
	pid = fork();
	if (pid == -1)
		return (free(path), EXIT_FAILURE);
	g_current_cmd_pid = pid;
	if (pid == 0)
	{
		ft_reset_signals();
		rl_clear_history();
		if (execve(path, cmd->args, data->env->env_array) == -1)
		{
			ft_cleanup_shell(data, first);
			exit(EXIT_FAILURE);
		}
	}
	free(path);
	return (ft_wait_for_child(pid));
}

int	ft_execute_builtin(t_cmd *cmd, t_data *data)
{
	if (!ft_strcmp(cmd->args[0], "echo"))
		return (ft_echo(cmd));
	if (!ft_strcmp(cmd->args[0], "cd"))
		return (ft_cd(cmd, data));
	if (!ft_strcmp(cmd->args[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd->args[0], "export"))
		return (ft_export(cmd, data));
	if (!ft_strcmp(cmd->args[0], "unset"))
		return (ft_unset(cmd, data));
	if (!ft_strcmp(cmd->args[0], "env"))
		return (ft_env(cmd, data));
	if (!ft_strcmp(cmd->args[0], "exit"))
		return (ft_exit(cmd, data));
	return (ERR_CMD_NOT_FOUND);
}

static int	ft_execute_single_cmd(t_cmd *cmd, t_data *data, \
int stdin_backup, int stdout_backup)
{
	int	result;

	if (ft_open_files(cmd) != SUCCESS)
		return (ft_restore_fds(stdin_backup, stdout_backup), EXIT_FAILURE);
	if (ft_setup_exec_redirections(cmd) != SUCCESS)
		return (ft_restore_fds(stdin_backup, stdout_backup), EXIT_FAILURE);
	result = ft_execute_cmd_with_args(cmd, data, cmd);
	return (result);
}

int	ft_execute_cmd(t_cmd *cmd, t_data *data, t_cmd *first)
{
	int	stdin_backup;
	int	stdout_backup;
	int	ret;
	int	heredoc_result;

	if (!cmd || !data)
		return (EXIT_FAILURE);
	heredoc_result = ft_handle_heredoc_preprocessing(cmd, first, data);
	if (heredoc_result != SUCCESS)
		return (heredoc_result);
	if (ft_backup_fds(&stdin_backup, &stdout_backup) != SUCCESS)
		return (EXIT_FAILURE);
	if (!cmd->next)
		ret = ft_execute_single_cmd(cmd, data, stdin_backup, stdout_backup);
	else
		ret = ft_exec_pipeline(cmd, data, first);
	ft_restore_fds(stdin_backup, stdout_backup);
	return (ret);
}
