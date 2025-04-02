/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:41:29 by aoger             #+#    #+#             */
/*   Updated: 2025/03/15 00:47:00 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_extract_cmd(t_ast *ast_node, t_token **token)
{
	t_token	*last_token;
	t_token	*current_token;
	t_token	*new_token;

	current_token = *token;
	ast_node->cmd_tokens = NULL;
	last_token = NULL;
	while (current_token && ft_is_token_operator(current_token))
	{
		new_token = ft_token_dup(current_token);
		if (!new_token)
			return (EXIT_FAILURE);
		if (!ast_node->cmd_tokens)
			ast_node->cmd_tokens = new_token;
		else
			last_token->next = new_token;
		last_token = new_token;
		current_token = current_token->next;
	}
	if (last_token)
		last_token->next = NULL;
	ast_node->type = AST_CMD;
	*token = current_token;
	return (SUCCESS);
}

static int	ft_is_op_same_prio(t_token *token, int priority, int *op_type)
{
	if (priority == PRIO_LOGIC_OP)
	{
		if (token->type == TOKEN_AND)
		{
			*op_type = AST_AND;
			return (1);
		}
		else if (token->type == TOKEN_OR)
		{
			*op_type = AST_OR;
			return (1);
		}
	}
	else if (priority == PRIO_PIPE && token->type == TOKEN_PIPE)
	{
		*op_type = AST_PIPE;
		return (1);
	}
	return (0);
}

static t_ast	*ft_build_group_or_cmd(t_token **token)
{
	t_ast	*ast_node;

	if (!*token)
		return (NULL);
	ast_node = ft_init_new_ast();
	if (!ast_node)
		return (NULL);
	if ((*token)->type == TOKEN_LPARENTH)
	{
		*token = (*token)->next;
		ast_node->type = AST_GROUP;
		ast_node->left = ft_build_ast(token, PRIO_LOGIC_OP);
		if (!*token || (*token)->type != TOKEN_RPARENTH)
			return (ft_free_ast_node(ast_node), NULL);
		*token = (*token)->next;
	}
	else
	{
		if (ft_extract_cmd(ast_node, token) != SUCCESS)
			return (ft_free_ast_node(ast_node), NULL);
	}
	return (ast_node);
}

t_ast	*ft_build_ast(t_token **token, int priority)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*op_node;
	int		op_type;

	if (priority > PRIO_PIPE)
		return (ft_build_group_or_cmd(token));
	left = ft_build_ast(token, priority + 1);
	if (!left)
		return (NULL);
	while (*token && ft_is_op_same_prio(*token, priority, &op_type))
	{
		op_node = ft_create_op_node(left, op_type);
		if (!op_node)
			return (ft_free_ast_node(left), NULL);
		*token = (*token)->next;
		right = ft_build_ast(token, priority + 1);
		if (!right)
			return (op_node->left = NULL, ft_free_ast_node(op_node), NULL);
		op_node->right = right;
		left = op_node;
	}
	return (left);
}
