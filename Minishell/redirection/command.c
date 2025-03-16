/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modembel <modembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:43:33 by modembel          #+#    #+#             */
/*   Updated: 2025/03/15 19:03:51 by modembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_outfile_fd(t_token *tok, t_cmd *cmd)
{
	char	*str;

	if (cmd->outfile >= 0)
		ft_close(cmd->outfile);
	if (!tok->next || tok->next->type <= 5)
	{
		ft_putstr_fd("parse error\n", STDERR_FILENO);
		g_exit_codes = 2;
		return (false);
	}
	str = tok->next->str;
	tok->next->type = FILE_NAME;
	if (tok->type == APPEND)
		cmd->outfile = open(str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		cmd->outfile = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (cmd->outfile == -1)
	{
		printf("%s\n", strerror(errno));
		return (false);
	}
	return (true);
}

bool	get_infile_fd(t_token *tok, t_cmd *cmd, t_data *data)
{
	char	*str;

	if (cmd->infile >= 0)
		ft_close(cmd->infile);
	if (!tok->next || tok->next->type <= 5)
	{
		ft_putstr_fd("parse error\n", STDERR_FILENO);
		g_exit_codes = 2;
		return (false);
	}
	str = tok->next->str;
	tok->next->type = FILE_NAME;
	if (tok->type == INPUT)
		cmd->infile = open(str, O_RDONLY, 0644);
	else
		cmd->infile = set_heredoc(str, data);
	if (cmd->infile == -1)
	{
		printf("%s\n", strerror(errno));
		return (false);
	}
	return (true);
}

bool	set_command(t_cmd **cmd, t_token *token, t_data *data)
{
	t_token	*tok;
	t_cmd	*command;

	tok = token;
	add_cmd(cmd, data);
	command = last_cmd((*cmd));
	while (tok && tok->type != PIPE)
	{
		if (tok->type == APPEND || tok->type == TRUNC)
		{
			if (!get_outfile_fd(tok, command))
				return (false);
		}
		else if (tok->type == HEREDOC || tok->type == INPUT)
		{
			if (!get_infile_fd(tok, command, data))
				return (false);
		}
		tok = tok->next;
	}
	command->param = get_param(token);
	return (true);
}

bool	check_pipe(t_data *data)
{
	t_token	*tok;

	tok = data->token;
	while (tok)
	{
		if (tok->type == PIPE)
		{
			if (!tok->prev || !tok->next)
			{
				g_exit_codes = 2;
				ft_putstr_fd("pipe syntax error\n", 2);
				return (false);
			}
		}
		tok = tok->next;
	}
	return (true);
}

bool	create_command(t_data *data)
{
	t_cmd	*cmd;
	t_token	*token;
	bool	succes;

	succes = true;
	cmd = data->cmd;
	if (!check_pipe(data))
		return (false);
	token = data->token;
	if (token)
		if (!set_command(&cmd, token, data))
			succes = false;
	token = token->next;
	while (token)
	{
		if (token->prev->type == PIPE)
			if (!set_command(&cmd, token, data))
				succes = false;
		token = token->next;
	}
	data->cmd = cmd;
	return (succes);
}
