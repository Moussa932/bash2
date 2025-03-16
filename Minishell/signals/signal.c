/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:25:48 by modembel          #+#    #+#             */
/*   Updated: 2025/03/03 07:21:04 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	handle_signal_parent(int num)
{
	g_exit_codes = num + 128;
}

void	set_signal_child(void)
{
	rl_event_hook = sig_event;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}


void	set_signal_parent(void)
{
	struct sigaction	sa;

	rl_event_hook = sig_event;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = if_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
