/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:37:01 by modembel          #+#    #+#             */
/*   Updated: 2025/03/03 07:25:30 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_valid_range(int sign, unsigned long long result)
{
	if ((sign == 1 && result > LONG_MAX) || (sign == -1 && result
			- 1 > LONG_MAX))
		return (1);
	return (0);
}

static int	value_length(char *str, int index)
{
	char	*dup;
	int		i;

	i = 0;
	dup = str + index;
	if (ft_strlen(dup) > 20)
		return (1);
	while (dup[i])
	{
		if (dup[i] == '-' || dup[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

static int	check_value(char *str, int index)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '-' && str[i] != '+')
		{
			if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
				return (1);
			if (str[i] > '9' || str[i] < '0')
				return (1);
		}
		i++;
	}
	if (value_length(str, index) == 1)
		return (1);
	return (0);
}

static int	ft_atol(char *str, int *valid)
{
	int					i;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	*valid = check_value(str, i);
	while (str[i] && str[i] >= '0' && str[i] <= '9' && *valid == 0)
	{
		result = result * 10 + str[i] - '0';
		*valid = check_valid_range(sign, result);
		i++;
	}
	return ((result * sign) % 256);
}

int	ft_exit(t_cmd *cmd, t_data *data)
{
	char	**arg;
	int		valid;

	arg = cmd->param;
	valid = 0;
	ft_putstr_fd("exit\n", 1);
	if (arg[1])
	{
		g_exit_codes = ft_atol(arg[1], &valid);
		if (valid != 0)
		{
			ft_putstr_fd("exit : numeric argument required\n", 2);
			exit_shell(data, 2, 0);
		}
	}
	if (arg[1] && arg[2])
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	exit_shell(data, g_exit_codes, 0);
	return (0);
}
