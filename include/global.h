/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthuroger <arthuroger@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:30:34 by aoger             #+#    #+#             */
/*   Updated: 2025/03/14 00:44:58 by arthuroger       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

// for received signals
extern int		g_signum;
// for handling rl_redisplay
extern pid_t	g_current_cmd_pid;

#endif