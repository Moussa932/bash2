/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:37:28 by modembel          #+#    #+#             */
/*   Updated: 2025/03/03 07:20:27 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	buff[PATH_MAX];

	if (cmd->param[1] != NULL)
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		return (1);
	}
	if (getcwd(buff, PATH_MAX))
	{
		printf("%s\n", buff);
		return (0);
	}
	else
	{
		ft_putstr_fd("pwd\n", 2);
		return (1);
	}
}
