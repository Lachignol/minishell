/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:29:07 by ascordil          #+#    #+#             */
/*   Updated: 2025/03/12 16:21:28 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_quote_char(char c, int *in_squote, int *in_dquote)
{
	if (c == '\'' && !(*in_dquote))
	{
		*in_squote = !(*in_squote);
		return (1);
	}
	else if (c == '"' && !(*in_squote))
	{
		*in_dquote = !(*in_dquote);
		return (1);
	}
	return (0);
}

static char	*ft_add_quote_type(char *quote_types, int in_squote, int in_dquote)
{
	char	*temp;
	char	quote_char;

	if (in_squote)
		quote_char = '1';
	else if (in_dquote)
		quote_char = '2';
	else
		quote_char = '0';
	temp = ft_charjoin(quote_types, quote_char);
	free(quote_types);
	return (temp);
}

static int	ft_process_char(char **result, char **quote_types, \
char c, int quote_state[2])
{
	*quote_types = ft_add_quote_type(*quote_types, quote_state[0], \
									quote_state[1]);
	if (!*quote_types)
		return (EXIT_FAILURE);
	*result = ft_charjoin_free(*result, c);
	if (!*result)
		return (EXIT_FAILURE);
	return (SUCCESS);
}

// quote_state[0] = in_squote
// quote_state[1] = in_dquote
static char	*ft_remove_quotes(t_token *token, char *content)
{
	char	*result;
	int		quote_state[2];
	char	*quote_types;
	size_t	i;

	if (ft_init_quote_removal(&result, &quote_types) != SUCCESS)
		return (NULL);
	i = 0;
	quote_state[0] = 0;
	quote_state[1] = 0;
	while (content[i])
	{
		if (ft_handle_quote_char(content[i], &quote_state[0], &quote_state[1]))
		{
			i++;
			continue ;
		}
		else if (ft_process_char(&result, &quote_types, content[i], \
				quote_state) != SUCCESS)
			return (free(result), free(quote_types), NULL);
		i++;
	}
	token->quote_types = quote_types;
	return (result);
}

int	ft_expand_quotes(t_token *token)
{
	t_token	*current;
	char	*unquoted;

	current = token;
	while (current)
	{
		if (current->type == TOKEN_WORD && current->content)
		{
			unquoted = ft_remove_quotes(current, current->content);
			if (!unquoted)
				return (EXIT_FAILURE);
			free(current->content);
			current->content = unquoted;
		}
		current = current->next;
	}
	return (SUCCESS);
}
