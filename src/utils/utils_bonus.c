/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:38:08 by aoger             #+#    #+#             */
/*   Updated: 2025/03/12 20:38:34 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_add_str_after_array(char **array, size_t *size, char *new_str)
{
	char	**new_array;

	new_array = malloc(sizeof(char *) * (*size + 2));
	if (!new_array)
		return (NULL);
	if (*size > 0)
		ft_memcpy(new_array, array, sizeof(char *) * (*size));
	new_array[*size] = ft_strdup(new_str);
	if (!new_array[*size])
		return (free(new_array), NULL);
	(*size)++;
	new_array[*size] = NULL;
	free(array);
	return (new_array);
}

int	ft_insert_strs_in_array(char ***array, char **strs, int strs_count, \
size_t insert_pos)
{
	char	**new_array;
	size_t	array_len;
	size_t	strs_after_pos;
	size_t	new_len;

	array_len = ft_str_arraylen((void **)*array);
	new_len = array_len + strs_count;
	new_array = malloc(sizeof(char *) * (new_len + 1));
	if (!new_array)
		return (EXIT_FAILURE);
	ft_memcpy(new_array, *array, insert_pos * sizeof(char *));
	ft_memcpy(&new_array[insert_pos], strs, strs_count * sizeof(char *));
	strs_after_pos = array_len - insert_pos;
	if (strs_after_pos > 0)
		ft_memcpy(&new_array[insert_pos + strs_count], \
				&(*array)[insert_pos + 1], strs_after_pos * sizeof(char *));
	new_array[new_len] = NULL;
	free(*array);
	*array = new_array;
	return (SUCCESS);
}

int	ft_has_wildcards(const char *str)
{
	size_t	i;
	int		in_squote;
	int		in_dquote;

	if (!str)
		return (0);
	in_squote = 0;
	in_dquote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (str[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (str[i] == '*' && !in_squote && !in_dquote)
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_ast_op(char c, char next_c)
{
	return ((c == '&' && next_c == '&') || c == '|' || c == '(' || c == ')');
}

int	ft_has_logical_operators(char *input)
{
	size_t	i;
	int		in_squotes;
	int		in_dquotes;

	i = 0;
	in_squotes = 0;
	in_dquotes = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_dquotes)
			in_squotes = !in_squotes;
		else if (input[i] == '"' && !in_squotes)
			in_dquotes = !in_dquotes;
		else if (!in_squotes && !in_dquotes)
		{
			if ((input[i] == '&' && input[i + 1] == '&') || \
				input[i] == '|' || \
				input[i] == '(' || input[i] == ')')
			{
				return (1);
			}
		}
		i++;
	}
	return (0);
}
