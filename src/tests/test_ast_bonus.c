/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:34:40 by aoger             #+#    #+#             */
/*   Updated: 2025/03/15 00:49:22 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_ast_type(int n)
{
	if (n == 0)
		printf("%s", "OR");
	else if (n == 1)
		printf("%s", "AND");
	else if (n == 2)
		printf("%s", "PIPE");
	else if (n == 3)
		printf("%s", "GROUP");
	else if (n == 4)
		printf("%s", "CMD");
}

void	ft_print_ast(t_ast *ast)
{
	if (!ast)
	{
		printf("(null)\n");
		return ;
	}
	ft_print_ast_type(ast->type);
	if (ast->type == AST_CMD && ast->cmd_tokens && ast->cmd_tokens->content)
		printf(" : [%s]", ast->cmd_tokens->content);
	printf("\n");
	if (ast->left)
	{
		printf("LEFT: ");
		ft_print_ast(ast->left);
	}
	if (ast->right)
	{
		printf("RIGHT: ");
		ft_print_ast(ast->right);
	}
}
