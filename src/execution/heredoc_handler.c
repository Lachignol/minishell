/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 01:05:48 by aoger             #+#    #+#             */
/*   Updated: 2025/03/09 23:45:37 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_read_heredoc_input(int fd, char *delimiter, int start_line)
{
	char			*line;
	int				lines_read;

	lines_read = 0;
	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		lines_read++;
		if (!line)
		{
			ft_print_eof_heredoc_warning(delimiter, start_line);
			break ;
		}
		if (!ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (lines_read);
}

static int	ft_write_heredoc_content(char *temp_file, char *delimiter, \
int start_line)
{
	int	fd;
	int	lines_read;

	fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	lines_read = ft_read_heredoc_input(fd, delimiter, start_line);
	close(fd);
	if (lines_read < 0)
	{
		unlink(temp_file);
		return (-1);
	}
	return (lines_read);
}

char	*ft_create_heredoc_file(void)
{
	static int	count;
	char		*filename;
	char		num[12];

	while (1)
	{
		ft_itoa_buffer(count++, num);
		filename = ft_strjoin("/tmp/.heredoc_", num);
		if (!filename)
			return (NULL);
		if (access(filename, F_OK) == -1)
			return (filename);
		free(filename);
		if (count > 99999)
			return (NULL);
	}
}

int	ft_handle_heredoc(t_redir *redir)
{
	int		lines_read;

	if (!redir->heredoc_file)
		return (-1);
	lines_read = ft_write_heredoc_content(redir->heredoc_file, \
					redir->heredoc_delim, redir->heredoc_start_line);
	if (lines_read < 0)
		return (-1);
	redir->fd = open(redir->heredoc_file, O_RDONLY);
	if (redir->fd == -1)
		return (-1);
	return (lines_read);
}
