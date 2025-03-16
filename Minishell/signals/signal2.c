/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:25:45 by modembel          #+#    #+#             */
/*   Updated: 2025/03/07 22:09:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_signal(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	if_sigint(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_exit_codes = 128 + sig;
	rl_done = 1;
}
