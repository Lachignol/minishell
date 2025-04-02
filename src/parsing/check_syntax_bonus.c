/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 20:08:07 by aoger             #+#    #+#             */
/*   Updated: 2025/03/14 20:50:02 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_parenth_token(t_token *token)
{
	return (token->type == TOKEN_LPARENTH || token->type == TOKEN_RPARENTH);
}

int	ft_is_operator_token(t_token *token)
{
	return (token->type == TOKEN_PIPE || token->type == TOKEN_OR || \
		token->type == TOKEN_AND);
}

int	ft_check_parentheses_balance(t_token *token)
{
	int		parenth_count;

	parenth_count = 0;
	while (token)
	{
		if (token->type == TOKEN_LPARENTH)
			parenth_count++;
		else if (token->type == TOKEN_RPARENTH)
		{
			parenth_count--;
			if (parenth_count < 0)
				return (ft_print_syntax_error(")"), ERR_SYNTAX);
		}
		token = token->next;
	}
	if (parenth_count > 0)
		return (ft_print_syntax_error(")"), ERR_SYNTAX);
	return (SUCCESS);
}
