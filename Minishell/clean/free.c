/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:28:21 by modembel          #+#    #+#             */
/*   Updated: 2025/03/03 07:19:03 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_data *data)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = data->cmd;
	while (cmd)
	{
		ft_close(cmd->outfile);
		ft_close(cmd->infile);
		if (cmd->param)
			free(cmd->param);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_token(t_data *data)
{
	t_token	*tok;
	t_token	*tmp;

	tok = data->token;
	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp->str);
		free(tmp);
	}
}

void	free_env(t_data *data)
{
	t_env	*env;
	t_env	*tmp;

	env = data->envlist;
	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->free)
			free(tmp->str);
		free(tmp);
	}
}

void	free_all(t_data *data)
{
	char	**arg;
	int		i;

	arg = data->tmps;
	i = 0;
	if (arg)
	{
		while (arg[i])
		{
			free(arg[i]);
			i++;
		}
		free(arg);
	}
	if (data->old_pwd)
		free(data->old_pwd);
	if (data->pwd)
		free(data->pwd);
	free_env(data);
	free_token(data);
	free_cmd(data);
	ft_close(data->save_stdout);
	ft_close(data->save_stdin);
}
