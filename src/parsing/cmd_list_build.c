/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_build.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:29:07 by ascordil          #+#    #+#             */
/*   Updated: 2025/03/14 00:51:16 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_add_argument(t_cmd *cmd, char *arg)
{
	char	**new_args;
	size_t	i;

	i = 0;
	while (cmd->args && cmd->args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (EXIT_FAILURE);
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	if (!new_args[i])
		return (free(new_args), EXIT_FAILURE);
	new_args[i + 1] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	return (SUCCESS);
}

static t_cmd	*ft_build_cmd(t_token **token, t_data *data)
{
	t_cmd	*cmd;

	cmd = ft_init_new_cmd();
	if (!cmd)
		return (NULL);
	while (*token && (*token)->type != TOKEN_PIPE)
	{
		if ((*token)->type == TOKEN_WORD)
		{
			if (ft_add_argument(cmd, (*token)->content) != SUCCESS)
				return (ft_free_cmd(cmd), NULL);
		}
		else if ((*token)->type == TOKEN_REDIR_IN \
			|| (*token)->type == TOKEN_REDIR_OUT \
			|| (*token)->type == TOKEN_HEREDOC \
			|| (*token)->type == TOKEN_APPEND)
		{
			if (ft_process_redirection(cmd, *token, data) != SUCCESS)
				return (ft_free_cmd(cmd), NULL);
			*token = (*token)->next;
		}
		*token = (*token)->next;
	}
	return (cmd);
}

t_cmd	*ft_build_cmd_list(t_token *token, t_data *data)
{
	t_cmd	*first;
	t_cmd	*current;
	t_token	*token_ptr;

	if (!token)
		return (NULL);
	token_ptr = token;
	first = ft_build_cmd(&token_ptr, data);
	if (!first)
		return (NULL);
	current = first;
	while (token_ptr && token_ptr->type == TOKEN_PIPE)
	{
		token_ptr = token_ptr->next;
		current->next = ft_build_cmd(&token_ptr, data);
		if (!current->next)
			return (ft_free_cmd(first), NULL);
		current = current->next;
	}
	return (first);
}
