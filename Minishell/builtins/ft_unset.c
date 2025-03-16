/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:37:34 by modembel          #+#    #+#             */
/*   Updated: 2025/03/07 03:48:10 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	var_disapear(t_env **envi, char *str)
{
	t_env	*env;

	env = (*envi);
	while (env)
	{
		if (ft_strncmp(env->str, str, env_size(env->str)) == 0)
		{
			if (env->next != NULL)
			{
				env->prev->next = env->next;
				env->next->prev = env->prev;
			}
			else
				env->prev->next = NULL;
			free(env);
			break ;
		}
		env = env->next;
	}
}

static int	first_index_disapear(t_env **envi, char *str)
{
	int		i;
	t_env	*env;

	env = (*envi);
	i = 0;
	while (env)
	{
		if (ft_strncmp(env->str, str, env_size(env->str)) == 0)
			break ;
		i++;
		env = env->next;
	}
	if (i == 0)
		return (1);
	return (0);
}

void	ft_unset(t_cmd *cmd, t_data *data, int index)
{
	t_env	*envi;

	envi = data->envlist;
	if (first_index_disapear(&envi, cmd->param[index]) == 1)
	{
		data->envlist = data->envlist->next;
		free(data->envlist->prev);
		data->envlist->prev = NULL;
		return ;
	}
	var_disapear(&envi, cmd->param[index]);
}

int	unset_all(t_cmd *cmd, t_data *data)
{
	int		i;
	t_env	*env;

	i = 0;
	env = data->envlist;
	if (!cmd->param[1])
	{
		ft_putstr_fd("unset: not enough arguments\n", 2);
		return (1);
	}
	while (cmd->param[i])
	{
		if (var_exist(cmd->param[i], &env) > -1)
			ft_unset(cmd, data, i);
		i++;
	}
	return (0);
}
