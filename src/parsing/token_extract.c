/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:29:07 by ascordil          #+#    #+#             */
/*   Updated: 2025/03/14 18:50:11 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_extract_quoted(char *str, size_t *i, char quote_type)
{
	char	*quoted;

	quoted = ft_strdup("");
	if (!quoted)
		return (NULL);
	quoted = ft_charjoin_free(quoted, str[*i]);
	if (!quoted)
		return (NULL);
	(*i)++;
	while (str[*i] && str[*i] != quote_type)
	{
		quoted = ft_charjoin_free(quoted, str[*i]);
		if (!quoted)
			return (NULL);
		(*i)++;
	}
	if (str[*i])
	{
		quoted = ft_charjoin_free(quoted, str[*i]);
		if (!quoted)
			return (NULL);
		(*i)++;
	}
	return (quoted);
}

static int	ft_handle_quotes(char **result, char *str, size_t *i)
{
	char	quote_type;
	char	*quoted;

	quote_type = str[*i];
	if (str[*i + 1] == quote_type)
		*i += 2;
	else if (ft_is_in_quotes(str, *i, quote_type))
	{
		quoted = ft_extract_quoted(str, i, quote_type);
		if (!quoted)
			return (EXIT_FAILURE);
		*result = ft_strjoin_free(*result, quoted);
		if (!*result)
			return (EXIT_FAILURE);
	}
	else
		(*i)++;
	return (SUCCESS);
}

static char	*ft_handle_word(char *str, size_t *i)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[*i] && !ft_is_shell_space(str[*i]) && !ft_is_operator(str[*i]))
	{
		if (ft_is_quote(str[*i]))
		{
			if (ft_handle_quotes(&result, str, i) != SUCCESS)
				return (free(result), NULL);
		}
		else
		{
			result = ft_charjoin_free(result, str[*i]);
			if (!result)
				return (NULL);
			(*i)++;
		}
	}
	return (result);
}

static char	*ft_handle_operator(char *str, size_t *i)
{
	char	*token;

	if (str[*i] != '(' && str[*i] != ')' && str[*i] == str[*i + 1])
	{
		if (str[*i] == '<' && str[*i + 2] == str[*i])
		{
			*i += 3;
			return (ft_strdup("<<<"));
		}
		token = ft_substr(str, *i, 2);
		*i += 2;
		return (token);
	}
	if (str[*i] == '<' && str[*i + 1] == '>')
	{
		*i += 2;
		return (ft_strdup("<>"));
	}
	token = ft_substr(str, *i, 1);
	(*i)++;
	return (token);
}

char	*ft_extract_token(char *str, size_t *i)
{
	if (ft_is_operator(str[*i]))
		return (ft_handle_operator(str, i));
	return (ft_handle_word(str, i));
}
