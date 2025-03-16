/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modembel <modembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:32:54 by modembel          #+#    #+#             */
/*   Updated: 2025/03/15 19:01:41 by modembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_in_env(t_env *env)
{
	int	i;
	int	j;

	j = 0;
	i = var_exist("PATH", &env);
	while (j++ < i)
		env = env->next;
	return (env->str);
}

void	free_path_error(char **path_env, char *command, t_cmd *cmd, int exit_c)
{
	int		i;
	t_data	*data;

	data = cmd->data;
	i = 0;
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (exit_c == 126)
		printf("%s : permission denied\n", cmd->param[0]);
	else if (ft_strchr(cmd->param[0], '/') != NULL && exit_c == 127)
		printf("no such file or directory: %s\n", cmd->param[0]);
	else if (exit_c == 127)
		printf("command not found: %s\n", cmd->param[0]);
	while (path_env[i])
	{
		free(path_env[i]);
		i++;
	}
	free(command);
	free(path_env);
	free_all(data);
	exit(exit_c);
}

char	*check_path(char *str, char **path, t_cmd *cmd, char *command)
{
	if (access(str, F_OK) == 0)
	{
		if (access(str, X_OK) == 0)
			return (str);
		if (!ft_strchr(cmd->param[0], '/'))
			free_path_error(path, command, cmd, 127);
		else
			free_path_error(path, command, cmd, 126);
	}
	return (NULL);
}

char	*path_search(char **path, t_cmd *cmd, char *command)
{
	int		i;
	char	*str;

	i = 0;
	str = cmd->param[0];
	if (check_path(str, path, cmd, command))
		return (str);
	str = NULL;
	while (path[i] && !ft_strchr(cmd->param[0], '/'))
	{
		str = ft_strjoin(path[i], command);
		if (access(str, F_OK) == 0)
		{
			if (access(str, X_OK) == 0)
				return (str);
			free(str);
			free_path_error(path, command, cmd, 126);
		}
		free(str);
		i++;
	}
	return (NULL);
}

char	*set_path_cmd(t_cmd *cmd, t_data *data, char ***path_env,
		char **command)
{
	char	*path;
	t_env	*env;

	env = data->envlist;
	if (!cmd->param[0])
	{
		free_all(data);
		data->cancel = true;
		exit(2);
	}
	if (!(cmd->param[0][0]))
	{
		free_all(data);
		exit(0);
	}
	*path_env = ft_split(path_in_env(env), ':');
	*command = ft_strjoin("/", cmd->param[0]);
	path = path_search(*path_env, cmd, *command);
	if (!path || !ft_strchr(path, '/'))
		free_path_error(*path_env, *command, cmd, 127);
	return (path);
}
