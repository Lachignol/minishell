/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_wildcards_handler_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:10:52 by arthuroger        #+#    #+#             */
/*   Updated: 2025/03/14 00:20:00 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_multiple_matches(t_redir *redir, char **matches)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(redir->filename, STDERR_FILENO);
	ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
	ft_free_array(matches);
	return (EXIT_FAILURE);
}

static int	ft_handle_single_match(t_redir *redir, char **matches)
{
	char	*old_filename;

	old_filename = redir->filename;
	redir->filename = ft_strdup(matches[0]);
	free(old_filename);
	ft_free_array(matches);
	if (!redir->filename)
		return (EXIT_FAILURE);
	return (SUCCESS);
}

static int	ft_count_wildcard_matches(char **matches)
{
	int	count;

	count = 0;
	while (matches && matches[count])
		count++;
	return (count);
}

int	ft_handle_redirection_wildcards(t_redir *redir)
{
	char	**matches;
	int		match_count;

	if (!ft_has_wildcards(redir->filename))
		return (SUCCESS);
	matches = ft_expand_wildcards(redir->filename);
	if (!matches)
		return (EXIT_FAILURE);
	match_count = ft_count_wildcard_matches(matches);
	if (match_count == 0)
		return (ft_free_array(matches), SUCCESS);
	else if (match_count == 1)
		return (ft_handle_single_match(redir, matches));
	else
		return (ft_handle_multiple_matches(redir, matches));
}
