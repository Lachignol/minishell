/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:29:07 by ascordil          #+#    #+#             */
/*   Updated: 2025/03/10 18:22:32 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_extract_variable_name(char *str, size_t *i, \
char *quote_types, char quote_type_start)
{
	size_t	start;
	char	*var_name;
	size_t	qt_len;

	qt_len = ft_strlen(quote_types);
	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		if (*i < qt_len && quote_types[*i] != quote_type_start)
			break ;
		(*i)++;
	}
	if (start == *i)
		return (ft_strdup("$"));
	var_name = ft_substr(str, start, *i - start);
	return (var_name);
}

static char	*ft_expand_variable(char *str, size_t *i, t_data *data, \
char *quote_types)
{
	char	*var_name;
	char	*value;
	size_t	pos;
	char	quote_type_start;

	pos = *i;
	if (quote_types && ft_is_in_single_quotes(quote_types, pos))
		return (ft_strdup("$"));
	if (str[*i + 1] == '?')
	{
		value = ft_itoa(data->exit_status);
		(*i)++;
		return (value);
	}
	quote_type_start = quote_types[*i];
	var_name = ft_extract_variable_name(str, i, quote_types, quote_type_start);
	if (!var_name)
		return (NULL);
	if (ft_strcmp(var_name, "$") == 0)
		return (var_name);
	value = ft_getenv(data->env, var_name);
	free(var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static int	ft_process_expansion(t_token *current, char **result, \
size_t *i, t_data *data)
{
	char	*var_value;

	var_value = ft_expand_variable(current->content, i, data, \
									current->quote_types);
	if (!var_value)
		return (free(*result), EXIT_FAILURE);
	if (current->content[*i] != '?' && current->content[*i])
		(*i)--;
	*result = ft_strjoin_free(*result, var_value);
	if (!*result)
		return (EXIT_FAILURE);
	return (SUCCESS);
}

static char	*ft_expand_content(t_token *current, t_data *data)
{
	char	*result;
	size_t	i;
	size_t	content_len;

	if (ft_init_expand_content(&result, &i, &content_len, current) != SUCCESS)
		return (NULL);
	while (i < content_len)
	{
		if (ft_should_expand(current, i))
		{
			if (ft_process_expansion(current, &result, &i, data) != SUCCESS)
				return (NULL);
		}
		else if (ft_is_dollar_before_quote(current, i))
		{
			i++;
			continue ;
		}
		else
			result = ft_charjoin_free(result, current->content[i]);
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}

int	ft_expand_variables(t_token *token, t_data *data)
{
	t_token	*current;
	char	*expanded;

	current = token;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			expanded = ft_expand_content(current, data);
			if (!expanded)
				return (EXIT_FAILURE);
			free(current->content);
			current->content = expanded;
		}
		current = current->next;
	}
	return (SUCCESS);
}
