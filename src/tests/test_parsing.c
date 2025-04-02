/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:41:32 by aoger             #+#    #+#             */
/*   Updated: 2025/02/27 23:09:07 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_token_type(int type)
{
	if (type == TOKEN_WORD)
		printf("WORD");
	else if (type == TOKEN_PIPE)
		printf("PIPE");
	else if (type == TOKEN_REDIR_IN)
		printf("INPUT");
	else if (type == TOKEN_REDIR_OUT)
		printf("OUTPUT");
	else if (type == TOKEN_HEREDOC)
		printf("HEREDOC");
	else if (type == TOKEN_APPEND)
		printf("APPEND");
}

static void	ft_print_redir(t_redir *redir)
{
	if (!redir)
		return ;
	while (redir)
	{
		if (redir->filename)
			printf("%s ", redir->filename);
		if (redir->heredoc_delim)
			printf("%s ", redir->heredoc_delim);
		if (redir->heredoc_file)
			printf("%s ", redir->heredoc_file);
		ft_print_token_type(redir->type);
		redir = redir->next;
		printf("\n");
	}
}

void	ft_print_cmd(t_cmd *cmd)
{
	size_t	i;
	size_t	cmd_num;

	if (!cmd)
	{
		printf("No cmd to print\n");
		return ;
	}
	cmd_num = 0;
	while (cmd)
	{
		printf("Cmd[%zu]\n", cmd_num++);
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			printf("'%s'", cmd->args[i]);
			if (cmd->args[i + 1])
				printf(", ");
			i++;
		}
		printf("\n");
		ft_print_redir(cmd->redirections);
		cmd = cmd->next;
	}
	printf("\n");
}

void	ft_print_tokens(t_token *tokens)
{
	t_token	*current;
	size_t	i;

	if (!tokens)
	{
		printf("No tokens to print\n");
		return ;
	}
	i = 0;
	current = tokens;
	while (current)
	{
		printf("Token[%zu]: '%s' '%s' (", i++, current->content, \
			current->quote_types);
		ft_print_token_type(current->type);
		printf(")\n");
		current = current->next;
	}
}
