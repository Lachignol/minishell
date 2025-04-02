/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:02:45 by aoger             #+#    #+#             */
/*   Updated: 2025/03/03 15:47:36 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_itoa_buffer(int n, char *buffer)
{
	char	*temp;

	temp = ft_itoa(n);
	if (!temp)
	{
		ft_strlcpy(buffer, "0", 2);
		return ;
	}
	ft_strlcpy(buffer, temp, ft_strlen(temp) + 1);
	free(temp);
}

char	*ft_charjoin(const char *str, char c)
{
	char	*new;
	size_t	i;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new = malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	new[i + 1] = '\0';
	return (new);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (temp);
}

char	*ft_charjoin_free(char *str, char c)
{
	char	*temp;

	temp = ft_charjoin(str, c);
	free(str);
	return (temp);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
