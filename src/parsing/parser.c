/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:29:07 by ascordil          #+#    #+#             */
/*   Updated: 2025/03/15 00:46:17 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef ENABLE_BONUS

t_ast	*ft_ast_parse_input(char *input, t_data *data)
{
	t_token	*token;
	t_token	*first_token;
	t_ast	*ast;
	int		status;

	if (!input || !*input)
		return (NULL);
	token = ft_tokenize(input, data);
	if (!token)
		return (NULL);
	first_token = token;
	status = ft_check_syntax(token);
	if (status != SUCCESS)
	{
		data->exit_status = status;
		return (ft_free_token_list(first_token), NULL);
	}
	ast = ft_build_ast(&token, PRIO_LOGIC_OP);
	if (ft_process_ast(ast, data) != SUCCESS)
		return (ft_free_token_list(first_token), ft_free_ast_node(ast), NULL);
	ft_free_token_list(first_token);
	return (ast);
}
#else

t_cmd	*ft_parse_input(char *input, t_data *data)
{
	t_token	*token;
	t_cmd	*cmd;
	int		status;

	if (!input || !*input)
		return (NULL);
	token = ft_tokenize(input, data);
	if (!token)
		return (NULL);
	status = ft_check_syntax(token);
	if (status != SUCCESS)
	{
		data->exit_status = status;
		return (ft_free_token_list(token), NULL);
	}
	cmd = ft_build_cmd_list(token, data);
	ft_free_token_list(token);
	return (cmd);
}
#endif
