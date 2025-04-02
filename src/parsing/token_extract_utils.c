/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_extract_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:29:07 by ascordil          #+#    #+#             */
/*   Updated: 2025/03/14 18:30:09 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifdef ENABLE_BONUS

int	ft_is_operator(int c)
{
	return (c == '>' || c == '<' || c == '|' || c == '&' \
	|| c == '(' || c == ')');
}

#else

int	ft_is_operator(int c)
{
	return (c == '>' || c == '<' || c == '|');
}
#endif

int	ft_is_in_quotes(char *str, size_t pos, char quote_type)
{
	pos++;
	while (str[pos] && str[pos] != quote_type)
		pos++;
	return (str[pos] == quote_type);
}

int	ft_is_quote(int c)
{
	return (c == '"' || c == '\'');
}
