/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:42:37 by aoger             #+#    #+#             */
/*   Updated: 2025/03/15 00:47:48 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_ast_node(t_ast *ast_node)
{
	if (!ast_node)
		return ;
	if (ast_node->left)
		ft_free_ast_node(ast_node->left);
	if (ast_node->right)
		ft_free_ast_node(ast_node->right);
	if (ast_node->cmd_tokens)
		ft_free_token_list(ast_node->cmd_tokens);
	free(ast_node);
}

t_ast	*ft_init_new_ast(void)
{
	t_ast	*ast_node;

	ast_node = malloc(sizeof(t_ast));
	if (!ast_node)
		return (NULL);
	ft_bzero(ast_node, sizeof(t_ast));
	return (ast_node);
}
