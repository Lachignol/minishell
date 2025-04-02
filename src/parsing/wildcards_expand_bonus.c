/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_expand_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:02:32 by aoger             #+#    #+#             */
/*   Updated: 2025/03/15 01:29:00 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// If when recursivity ends *strings is null,
// it means it corresponds to the pattern
static int	ft_match_wildcard(const char *pattern, const char *string)
{
	if (!*pattern)
		return (!*string);
	if (*pattern == '*')
	{
		if (ft_match_wildcard(pattern + 1, string))
			return (1);
		if (*string && ft_match_wildcard(pattern, string + 1))
			return (1);
		return (0);
	}
	if (*string && *pattern == *string)
		return (ft_match_wildcard(pattern + 1, string + 1));
	return (0);
}

static char	**ft_collect_matching_files(DIR *dir, const char *pattern, \
size_t *count)
{
	struct dirent	*entry;
	char			**matches;

	matches = ft_calloc(1, sizeof(char *));
	if (!matches)
		return (NULL);
	*count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
		{
			entry = readdir(dir);
			continue ;
		}
		if (ft_match_wildcard(pattern, entry->d_name))
		{
			matches = ft_add_str_after_array(matches, count, entry->d_name);
			if (!matches)
				return (NULL);
		}
		entry = readdir(dir);
	}
	return (matches);
}

char	**ft_expand_wildcards(const char *pattern)
{
	DIR				*dir;
	char			**matches;
	size_t			count;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	matches = ft_collect_matching_files(dir, pattern, &count);
	closedir(dir);
	if (!matches)
		return (NULL);
	if (count == 0)
	{
		free(matches);
		matches = malloc(sizeof(char *) * 2);
		if (!matches)
			return (NULL);
		matches[0] = ft_strdup(pattern);
		if (!matches[0])
			return (free(matches), NULL);
		matches[1] = NULL;
	}
	else
		ft_sort_str_array(matches, count);
	return (matches);
}

static int	ft_add_expansions_to_cmd_args(t_cmd *cmd, size_t *i, \
char **expansions, size_t expansion_count)
{
	free(cmd->args[*i]);
	if (ft_insert_strs_in_array(&(cmd->args), expansions, expansion_count, *i) \
	!= SUCCESS)
		return (ft_free_array(expansions), EXIT_FAILURE);
	free(expansions);
	*i += expansion_count - 1;
	return (SUCCESS);
}

int	ft_expand_cmd_wildcards(t_cmd *cmd)
{
	size_t	i;
	char	**expansions;
	size_t	expansion_count;

	if (!cmd || !cmd->args)
		return (SUCCESS);
	i = 0;
	while (cmd->args[i])
	{
		if (ft_has_wildcards(cmd->args[i]))
		{
			expansions = ft_expand_wildcards(cmd->args[i]);
			if (!expansions)
				return (EXIT_FAILURE);
			expansion_count = 0;
			while (expansions[expansion_count])
				expansion_count++;
			if (expansion_count > 0 && \
			ft_add_expansions_to_cmd_args(cmd, &i, expansions, \
			expansion_count) != SUCCESS)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
