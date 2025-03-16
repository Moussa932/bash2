/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modembel <modembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:30:15 by modembel          #+#    #+#             */
/*   Updated: 2025/03/15 18:59:54 by modembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_path_errorr(char **path_env, char *command, t_cmd *cmd, int exit_c)
{
	int		i;
	t_data	*data;

	data = cmd->data;
	i = 0;
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (exit_c == 126)
		printf("%s : is a directory\n", cmd->param[0]);
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
int	child_process(t_cmd *command, t_data *data)
{
	char	*cmd_path;
	int		exit_c;
	char	**path_env;
	char	*cmd;

	path_env = NULL;
	cmd = NULL;
	child_signal();
	if (identifie_builtin(command->param[0]) == 0)
	{
		exit_c = start_builtins(data, command);
		free_all(data);
		exit(exit_c);
	}
	cmd_path = set_path_cmd(command, data, &path_env, &cmd);
	if (command->outfile > 0)
		dup2(command->outfile, STDOUT_FILENO);
	if (command->infile > 0)
		dup2(command->infile, STDIN_FILENO);
	if (execve(cmd_path, command->param, data->env) == -1)
	{
		if (ft_strchr(cmd_path, '/') != NULL)
			free_path_errorr(path_env, cmd, command, 126);
		free_path_error(path_env, cmd, command, 2);
	}
	free_all(data);
	exit(0);
}

int	identifie_builtin(char *arg)
{
	if (!arg)
		return (1);
	if (ft_strncmp("cd", arg, 2) == 0)
		return (0);
	else if (ft_strncmp("echo", arg, 5) == 0)
		return (0);
	else if (ft_strncmp("env", arg, 3) == 0)
		return (0);
	else if (ft_strncmp("export", arg, 6) == 0)
		return (0);
	else if (ft_strncmp("pwd", arg, 3) == 0)
		return (0);
	else if (ft_strncmp("unset", arg, 5) == 0)
		return (0);
	else if (ft_strncmp("exit", arg, 5) == 0)
		return (0);
	return (1);
}

int	start_builtins(t_data *data, t_cmd *cmd)
{
	char	*arg;
	int		exit;

	if (cmd->outfile > -1)
		dup2(cmd->outfile, STDOUT_FILENO);
	arg = cmd->param[0];
	if (ft_strncmp("cd", arg, 2) == 0)
		exit = ft_cd(cmd, data);
	else if (ft_strncmp("echo", arg, 5) == 0)
		exit = ft_echo(cmd);
	else if (ft_strncmp("env", arg, 3) == 0)
		exit = ft_env(cmd, data);
	else if (ft_strncmp("export", arg, 6) == 0)
		exit = export_all(cmd, data);
	else if (ft_strncmp("pwd", arg, 3) == 0)
		exit = ft_pwd(cmd);
	else if (ft_strncmp("unset", arg, 5) == 0)
		exit = unset_all(cmd, data);
	else if (ft_strncmp("exit", arg, 5) == 0)
		exit = ft_exit(cmd, data);
	dup2(data->save_stdout, STDOUT_FILENO);
	return (exit);
}
