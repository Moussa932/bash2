/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:28:16 by modembel          #+#    #+#             */
/*   Updated: 2025/03/03 07:19:18 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_data *data, int ex_code, int ctrl_d)
{
	if (ctrl_d == 1)
		ft_putstr_fd("exit\n", 1);
	free_all(data);
	exit(ex_code);
}
