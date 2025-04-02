/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_process_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:56:35 by aoger             #+#    #+#             */
/*   Updated: 2025/03/15 00:45:45 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_process_ast(t_ast *ast_node, t_data *data)
{
	if (!ast_node)
		return (CONTINUE_SHELL);
	if (ast_node->type == AST_CMD && ast_node->cmd_tokens)
	{
		ast_node->cmd = ft_build_cmd_list(ast_node->cmd_tokens, data);
		if (!ast_node->cmd)
			return (data->exit_status = ERR_MEMORY, ERR_MEMORY);
		if (ft_expand_cmd_wildcards(ast_node->cmd) != SUCCESS)
			return (data->exit_status = ERR_MEMORY, ERR_MEMORY);
	}
	if (ast_node->left && ft_process_ast(ast_node->left, data) \
	!= SUCCESS)
		return (data->exit_status);
	if (ast_node->right && ft_process_ast(ast_node->right, data) \
	!= SUCCESS)
		return (data->exit_status);
	return (SUCCESS);
}
