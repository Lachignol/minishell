/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:16:18 by aoger             #+#    #+#             */
/*   Updated: 2025/03/14 12:24:01 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signum = 0;
pid_t	g_current_cmd_pid = 0;

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)ac;
	(void)av;
	if (ft_init_shell(&data, envp) != SUCCESS)
		return (ERR_MEMORY);
	ft_handle_signals();
	ft_shell_loop(&data);
	ft_cleanup_shell(&data, NULL);
	return (data.exit_status);
}
