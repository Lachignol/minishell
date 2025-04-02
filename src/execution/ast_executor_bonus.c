/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_executor_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:02:43 by aoger             #+#    #+#             */
/*   Updated: 2025/03/14 18:23:37 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// function to avoid double free with ft_cleanup_shell
static void	ft_set_ast_cmds_to_null(t_ast *ast_node)
{
	if (!ast_node)
		return ;
	if (ast_node->type == AST_CMD)
		ast_node->cmd = NULL;
	if (ast_node->left)
		ft_set_ast_cmds_to_null(ast_node->left);
	if (ast_node->right)
		ft_set_ast_cmds_to_null(ast_node->right);
}

static t_cmd	*ft_connect_pipeline(t_cmd *left_cmds, t_cmd *right_cmds)
{
	t_cmd	*last_left_cmd;

	if (!left_cmds)
		return (right_cmds);
	if (!right_cmds)
		return (left_cmds);
	last_left_cmd = left_cmds;
	while (last_left_cmd->next)
		last_left_cmd = last_left_cmd->next;
	last_left_cmd->next = right_cmds;
	return (left_cmds);
}

static t_cmd	*ft_build_pipeline_from_ast(t_ast *ast_node)
{
	t_cmd	*left_cmds;
	t_cmd	*right_cmds;

	if (!ast_node)
		return (NULL);
	if (ast_node->type == AST_CMD)
		return (ast_node->cmd);
	else if (ast_node->type == AST_GROUP && ast_node->left)
		return (ft_build_pipeline_from_ast(ast_node->left));
	else if (ast_node->type != AST_PIPE)
		return (NULL);
	left_cmds = ft_build_pipeline_from_ast(ast_node->left);
	right_cmds = ft_build_pipeline_from_ast(ast_node->right);
	return (ft_connect_pipeline(left_cmds, right_cmds));
}

static int	ft_execute_ast_pipe(t_ast *ast_node, t_data *data)
{
	t_cmd	*pipeline;

	pipeline = ft_build_pipeline_from_ast(ast_node);
	if (!pipeline)
		return (EXIT_FAILURE);
	data->exit_status = ft_execute_cmd(pipeline, data, pipeline);
	ft_set_ast_cmds_to_null(ast_node);
	return (data->exit_status);
}

int	ft_execute_ast(t_ast *ast_node, t_data *data)
{
	if (!ast_node)
		return (data->exit_status);
	if (ast_node->type == AST_OR || ast_node->type == AST_AND || \
	ast_node->type == AST_GROUP)
	{
		data->exit_status = ft_execute_ast(ast_node->left, data);
		if (ast_node->type == AST_OR && data->exit_status != 0)
			data->exit_status = ft_execute_ast(ast_node->right, data);
		else if (ast_node->type == AST_AND && data->exit_status == 0)
			data->exit_status = ft_execute_ast(ast_node->right, data);
		return (data->exit_status);
	}
	else if (ast_node->type == AST_PIPE)
		return (ft_execute_ast_pipe(ast_node, data));
	else if (ast_node->type == AST_CMD && ast_node->cmd)
	{
		data->exit_status = ft_execute_cmd(ast_node->cmd, data, ast_node->cmd);
		ast_node->cmd = NULL;
	}
	return (data->exit_status);
}
