/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:25:59 by aoger             #+#    #+#             */
/*   Updated: 2025/03/14 00:42:32 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_redir
{
	char			*filename;
	char			*heredoc_file;
	char			*heredoc_delim;
	int				heredoc_start_line;
	int				type;
	int				fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirections;
	int				pipe[2];
	int				pid;
	struct s_cmd	*next;
}	t_cmd;

// quote_types: 0 no quote, 1 -> ', 2 -> "
typedef struct s_token
{
	char			*content;
	int				type;
	char			*quote_types;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char	**env_array;
	size_t	size;
}	t_env;

typedef struct s_data
{
	t_env	*env;
	int		exit_status;
	int		line_count;
}	t_data;

#endif