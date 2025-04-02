/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:29:07 by ascordil          #+#    #+#             */
/*   Updated: 2025/03/14 18:35:03 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef ENABLE_BONUS

static int	ft_get_token_type(char *content)
{
	if (!ft_strcmp(content, "||"))
		return (TOKEN_OR);
	else if (!ft_strcmp(content, "&&"))
		return (TOKEN_AND);
	else if (!ft_strcmp(content, "("))
		return (TOKEN_LPARENTH);
	else if (!ft_strcmp(content, ")"))
		return (TOKEN_RPARENTH);
	else if (!ft_strcmp(content, "|"))
		return (TOKEN_PIPE);
	else if (!ft_strcmp(content, "<"))
		return (TOKEN_REDIR_IN);
	else if (!ft_strcmp(content, "<<"))
		return (TOKEN_HEREDOC);
	else if (!ft_strcmp(content, ">"))
		return (TOKEN_REDIR_OUT);
	else if (!ft_strcmp(content, ">>"))
		return (TOKEN_APPEND);
	else if (!ft_strcmp(content, "<<<"))
		return (TOKEN_TRIPLEIN);
	else if (!ft_strcmp(content, "<>"))
		return (TOKEN_INOUT);
	return (TOKEN_WORD);
}
#else

static int	ft_get_token_type(char *content)
{
	if (!ft_strcmp(content, "|"))
		return (TOKEN_PIPE);
	else if (!ft_strcmp(content, "<"))
		return (TOKEN_REDIR_IN);
	else if (!ft_strcmp(content, "<<"))
		return (TOKEN_HEREDOC);
	else if (!ft_strcmp(content, ">"))
		return (TOKEN_REDIR_OUT);
	else if (!ft_strcmp(content, ">>"))
		return (TOKEN_APPEND);
	else if (!ft_strcmp(content, "<<<"))
		return (TOKEN_TRIPLEIN);
	else if (!ft_strcmp(content, "<>"))
		return (TOKEN_INOUT);
	return (TOKEN_WORD);
}
#endif

static t_token	*ft_create_next_token(char *input, size_t *i)
{
	t_token	*new;
	char	*content;
	int		type;

	content = ft_extract_token(input, i);
	if (!content)
		return (NULL);
	type = ft_get_token_type(content);
	new = ft_create_token(content, type);
	free(content);
	return (new);
}

void	ft_skip_spaces(char *input, size_t *i)
{
	while (input[*i] && ft_is_shell_space(input[*i]))
		(*i)++;
}

t_token	*ft_tokenize(char *input, t_data *data)
{
	t_token	*token;
	t_token	*new;
	size_t	i;

	token = NULL;
	i = 0;
	while (input[i])
	{
		ft_skip_spaces(input, &i);
		if (!input[i])
			break ;
		new = ft_create_next_token(input, &i);
		if (!new)
			return (ft_free_token_list(token), NULL);
		ft_add_token(&token, new);
	}
	if (ft_expand_quotes(token) != SUCCESS)
		return (ft_free_token_list(token), NULL);
	if (ft_expand_variables(token, data) != SUCCESS)
		return (ft_free_token_list(token), NULL);
	return (token);
}
