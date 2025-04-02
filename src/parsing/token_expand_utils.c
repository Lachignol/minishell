/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:29:07 by ascordil          #+#    #+#             */
/*   Updated: 2025/03/10 17:57:40 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_dollar_before_quote(t_token *current, size_t pos)
{
	size_t	quote_len;

	if (!current->quote_types)
		return (0);
	quote_len = ft_strlen(current->quote_types);
	if (pos >= quote_len || pos + 1 >= quote_len)
		return (0);
	return (current->content[pos] == '$' && \
			current->quote_types[pos] && \
			current->quote_types[pos + 1] && \
			current->quote_types[pos] != current->quote_types[pos + 1]);
}

int	ft_should_expand(t_token *current, size_t pos)
{
	char	c;
	char	next_c;
	char	*quote_types;
	size_t	quote_len;

	c = current->content[pos];
	next_c = current->content[pos + 1];
	quote_types = current->quote_types;
	if (!quote_types)
		return (0);
	quote_len = ft_strlen(quote_types);
	if (pos >= quote_len || pos + 1 >= quote_len)
		return (0);
	return (c == '$' && next_c && \
			quote_types[pos] && quote_types[pos + 1] && \
			quote_types[pos] == quote_types[pos + 1] && \
			(ft_isalnum(next_c) || next_c == '_' || next_c == '?') && \
			!ft_is_in_single_quotes(quote_types, pos));
}

int	ft_init_expand_content(char **result, size_t *i, \
size_t *content_len, t_token *current)
{
	*result = ft_strdup("");
	if (!*result)
		return (EXIT_FAILURE);
	*i = 0;
	*content_len = ft_strlen(current->content);
	return (SUCCESS);
}

int	ft_init_quote_removal(char **result, char **quote_types)
{
	*result = ft_strdup("");
	*quote_types = ft_strdup("");
	if (!*result || !*quote_types)
	{
		free(*result);
		free(*quote_types);
		return (EXIT_FAILURE);
	}
	return (SUCCESS);
}

int	ft_is_in_single_quotes(char *quote_types, int pos)
{
	if (!quote_types || pos < 0 || pos >= (int)ft_strlen(quote_types))
		return (0);
	return (quote_types[pos] == '1');
}
