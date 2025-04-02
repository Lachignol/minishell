/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:12:40 by ascordil          #+#    #+#             */
/*   Updated: 2025/03/14 21:08:50 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef ENABLE_BONUS

static int	ft_check_parenth(t_token *token, t_token *prev_token)
{
	if (token->type == TOKEN_LPARENTH)
	{
		if (token->next && token->next->type == TOKEN_RPARENTH)
			return (ft_print_syntax_error("()"), ERR_SYNTAX);
	}
	else if (token->type == TOKEN_RPARENTH)
	{
		if (!prev_token || ft_is_operator_token(prev_token))
			return (ft_print_syntax_error(token->content), ERR_SYNTAX);
	}
	return (SUCCESS);
}

static int	ft_check_op(t_token *token, t_token *prev_token)
{
	if (!prev_token || prev_token->type == TOKEN_PIPE || \
	prev_token->type == TOKEN_AND || prev_token->type == TOKEN_OR)
	{
		ft_print_syntax_error(token->content);
		return (ERR_SYNTAX);
	}
	if (!token->next || token->next->type == TOKEN_PIPE || \
	token->next->type == TOKEN_AND || token->next->type == TOKEN_OR)
	{
		if (!token->next)
			ft_print_syntax_error("newline");
		else
			ft_print_syntax_error(token->next->content);
		return (ERR_SYNTAX);
	}
	return (SUCCESS);
}

int	ft_check_syntax(t_token *token)
{
	t_token	*current;
	t_token	*prev;
	int		status;

	if (ft_check_parentheses_balance(token) != SUCCESS)
		return (ERR_SYNTAX);
	current = token;
	prev = NULL;
	status = 0;
	while (current)
	{
		if (ft_is_redirection_token(current))
			status = ft_check_redirection(current);
		else if (ft_is_operator_token(current))
			status = ft_check_op(current, prev);
		else if (ft_is_parenth_token(current))
			status = ft_check_parenth(current, prev);
		if (status == ERR_SYNTAX)
			return (status);
		prev = current;
		current = current->next;
	}
	return (SUCCESS);
}

#else

static int	ft_check_op(t_token *token, t_token *prev_token)
{
	if (!prev_token || prev_token->type == TOKEN_PIPE)
	{
		ft_print_syntax_error(token->content);
		return (ERR_SYNTAX);
	}
	if (!token->next || token->next->type == TOKEN_PIPE)
	{
		if (!token->next)
			ft_print_syntax_error("newline");
		else
			ft_print_syntax_error(token->next->content);
		return (ERR_SYNTAX);
	}
	return (SUCCESS);
}

int	ft_check_syntax(t_token *token)
{
	t_token	*current;
	t_token	*prev;
	int		status;

	current = token;
	prev = NULL;
	status = 0;
	while (current)
	{
		if (ft_is_redirection_token(current))
			status = ft_check_redirection(current);
		else if (current->type == TOKEN_PIPE)
			status = ft_check_op(current, prev);
		if (status == ERR_SYNTAX)
			return (status);
		prev = current;
		current = current->next;
	}
	return (SUCCESS);
}
#endif
