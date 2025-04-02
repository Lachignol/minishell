/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoger <aoger@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:23:11 by aoger             #+#    #+#             */
/*   Updated: 2025/03/13 17:34:09 by aoger            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/* PROMPT DEFINITION */
# define PROMPT "minishell$ "	// Shell prompt displayed to user
# define HEREDOC_PROMPT "> "

/* TOKEN TYPES */
# define TOKEN_WORD 0		// Commands (ls), arguments (-l), filenames (f.txt)
# define TOKEN_PIPE 1		// |
# define TOKEN_REDIR_IN 2	// <
# define TOKEN_REDIR_OUT 3	// >
# define TOKEN_APPEND 4		// >>
# define TOKEN_HEREDOC 5	// <<
# define TOKEN_TRIPLEIN 6	// <<<
# define TOKEN_INOUT 7		// <>

/* SHELL LOOP STATUS */
# define CONTINUE_SHELL 0
# define EXIT_SHELL 1

/* STATUS CODES */
// General Shell Status Codes
# define SUCCESS 0
# define ERR_MEMORY 1
# define ERR_SYNTAX 2
// Execution Errors (120-127)
# define ERR_CMD_NOT_FOUND 127
// Signal Errors
# define ERR_SIGNAL_BASE 128
# define ERR_CTRL_C 130			// 128 + SIGINT(2)
# define ERR_CTRL_SLASH 131		// 128 + SIGQUIT(3)

#endif