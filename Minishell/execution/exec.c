/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:34:35 by modembel          #+#    #+#             */
/*   Updated: 2025/03/07 22:12:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_code_if_signaled(int status)
{
	if (WIFEXITED(status))
		g_exit_codes = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_codes = 128 + WTERMSIG(status);
	else if (WIFSTOPPED(status))
		g_exit_codes = 128 + WSTOPSIG(status);
}

void	wait_child(t_data *data)
{
	int		status;
	pid_t	wait;

	wait = 0;
	while (wait != -1)
	{
		wait = waitpid(-1, &status, 0);
		set_code_if_signaled(status);
		if (wait == data->pid)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->exit_code = 128 + WTERMSIG(status);
			else if (WIFSTOPPED(status))
				data->exit_code = 128 + WSTOPSIG(status);
		}
	}
	if (g_exit_codes == 128 + SIGQUIT)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	g_exit_codes = data->exit_code;
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		set_signal_child();
	}
	return (pid);
}

void	exec_two(t_data *data, t_cmd *cmd)
{
	int	pipe_fd[2];

	while (cmd)
	{
		pipe(pipe_fd);
		data->pid = ft_fork();
		if (data->pid == 0)
		{
			ft_close(pipe_fd[0]);
			if (cmd->next)
				dup2(pipe_fd[1], STDOUT_FILENO);
			child_process(cmd, data);
			ft_close(pipe_fd[1]);
		}
		ft_close(pipe_fd[1]);
		if (cmd->next)
			dup2(pipe_fd[0], STDIN_FILENO);
		else
			dup2(data->save_stdin, STDIN_FILENO);
		ft_close(pipe_fd[0]);
		cmd = cmd->next;
	}
	wait_child(data);
}

int	exec(t_data *data, t_cmd *cmd)
{
	set_signal_parent();
	if (data->cancel)
		return (0);
	if (cmd && !cmd->prev && !cmd->next
		&& identifie_builtin(cmd->param[0]) == 0)
		g_exit_codes = start_builtins(data, cmd);
	else
	{
		data->cmd = cmd;
		exec_two(data, cmd);
	}
	return (0);
}
