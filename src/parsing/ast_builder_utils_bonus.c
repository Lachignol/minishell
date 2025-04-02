/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:42:18 by aoger             #+#    #+#             */
/*   Updated: 2025/03/15 00:17:45 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token_dup(t_token *token)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	ft_bzero(new_token, sizeof(t_token));
	new_token->content = ft_strdup(token->content);
	if (!new_token->content)
		return (free(new_token), NULL);
	new_token->type = token->type;
	new_token->next = NULL;
	return (new_token);
}

int	ft_is_token_operator(t_token *token)
{
	return (token && (token->type == TOKEN_WORD || \
	token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT || \
	token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC));
}

t_ast	*ft_create_op_node(t_ast *left, int op_type)
{
	t_ast	*op_node;

	op_node = ft_init_new_ast();
	if (!op_node)
		return (NULL);
	op_node->type = op_type;
	op_node->left = left;
	return (op_node);
}
