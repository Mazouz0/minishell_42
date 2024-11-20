/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohmazou <mohmazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:01:59 by mohmazou          #+#    #+#             */
/*   Updated: 2024/11/08 12:40:40 by mohmazou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	int_handel(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit_status(1);
}

void	ft_sig_herdoc(int sig)
{
	(void)sig;
	close(STDIN_FILENO);
	exit_status(-1337);
	g_sig = 0;
}

void	ft_handle_signals(void)
{
	signal(SIGINT, int_handel);
	signal(SIGQUIT, SIG_IGN);
}
