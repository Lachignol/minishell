/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:39:58 by aoger             #+#    #+#             */
/*   Updated: 2025/03/14 20:19:20 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redirection_token(t_token *token)
{
	return (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT || \
		token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC || \
		token->type == TOKEN_TRIPLEIN || token->type == TOKEN_INOUT);
}

char	*ft_get_redir_error_token(t_token *token)
{
	if (!token->next)
		return (ft_strdup("newline"));
	if (token->next->type != TOKEN_WORD)
		return (ft_strdup(token->next->content));
	return (ft_strdup("newline"));
}

int	ft_check_redirection(t_token *token)
{
	char	*error_token;

	if (!token->next || token->next->type != TOKEN_WORD)
	{
		error_token = ft_get_redir_error_token(token);
		if (!error_token)
			return (ERR_MEMORY);
		ft_print_syntax_error(error_token);
		return (free(error_token), ERR_SYNTAX);
	}
	return (SUCCESS);
}
