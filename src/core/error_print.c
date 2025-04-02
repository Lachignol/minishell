/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:12:16 by aoger             #+#    #+#             */
/*   Updated: 2025/03/06 23:32:07 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_null_path_error(t_cmd *cmd)
{
	if (ft_strchr(cmd->args[0], '/'))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(cmd->args[0]);
	}
	else
	{
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
}

int	ft_print_eof_heredoc_warning(char *delimiter, int start_line)
{
	char	*start_line_str;

	ft_putstr_fd("minishell: warning: here-document at line ", \
		STDERR_FILENO);
	start_line_str = ft_itoa(start_line);
	if (!start_line_str)
		return (EXIT_FAILURE);
	ft_putstr_fd(start_line_str, STDERR_FILENO);
	free(start_line_str);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
	return (SUCCESS);
}

void	ft_print_syntax_error(char *error_token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", \
		STDERR_FILENO);
	ft_putstr_fd(error_token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
