/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_preprocess.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:40:16 by aoger             #+#    #+#             */
/*   Updated: 2025/03/14 00:46:45 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_heredoc_parent(int *pipe_fd, void (*old_sigint)(int), \
pid_t pid, t_data *data)
{
	int	status;
	int	lines_read;

	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	g_current_cmd_pid = 0;
	signal(SIGINT, old_sigint);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
	{
		if (read(pipe_fd[0], &lines_read, sizeof(int)) > 0)
			data->line_count += lines_read;
	}
	close(pipe_fd[0]);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (130);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (SUCCESS);
}

static void	ft_handle_heredoc_child(t_redir *redir, int *pipe_fd, \
t_cmd *first, t_data *data)
{
	int	lines_read;

	close(pipe_fd[0]);
	signal(SIGINT, SIG_DFL);
	ft_setup_heredoc_signals();
	lines_read = ft_handle_heredoc(redir);
	if (lines_read <= 0)
	{
		close(pipe_fd[1]);
		ft_cleanup_heredoc_shell(data, first);
		exit(EXIT_FAILURE);
	}
	write(pipe_fd[1], &lines_read, sizeof(int));
	close(pipe_fd[1]);
	ft_cleanup_heredoc_shell(data, first);
	exit(EXIT_SUCCESS);
}

static int	ft_process_heredoc(t_redir *redir, t_cmd *first, t_data *data)
{
	pid_t	pid;
	void	(*old_sigint)(int);
	int		pipe_fd[2];
	char	*temp_file;

	temp_file = ft_create_heredoc_file();
	if (!temp_file)
		return (EXIT_FAILURE);
	free(redir->heredoc_file);
	redir->heredoc_file = temp_file;
	if (pipe(pipe_fd) == -1)
		return (EXIT_FAILURE);
	old_sigint = signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		signal(SIGINT, old_sigint);
		return (EXIT_FAILURE);
	}
	g_current_cmd_pid = pid;
	if (pid == 0)
		ft_handle_heredoc_child(redir, pipe_fd, first, data);
	return (ft_handle_heredoc_parent(pipe_fd, old_sigint, pid, data));
}

static int	ft_preprocess_all_heredocs(t_cmd *cmd, t_cmd *first, t_data *data)
{
	t_cmd	*current;
	t_redir	*redir;
	int		result;

	current = cmd;
	while (current)
	{
		redir = current->redirections;
		while (redir)
		{
			if (redir->type == TOKEN_HEREDOC)
			{
				result = ft_process_heredoc(redir, first, data);
				if (result != SUCCESS)
					return (result);
			}
			redir = redir->next;
		}
		current = current->next;
	}
	return (SUCCESS);
}

int	ft_handle_heredoc_preprocessing(t_cmd *cmd, t_cmd *first, t_data *data)
{
	int	heredoc_status;

	heredoc_status = ft_preprocess_all_heredocs(cmd, first, data);
	if (heredoc_status != SUCCESS)
	{
		if (heredoc_status == 130)
			return (130);
		return (EXIT_FAILURE);
	}
	return (SUCCESS);
}
