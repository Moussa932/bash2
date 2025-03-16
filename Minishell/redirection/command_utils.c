/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:43:23 by modembel          #+#    #+#             */
/*   Updated: 2025/03/09 11:35:14 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*last_cmd(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd != NULL && cmd->next == NULL)
			return (cmd);
		cmd = cmd->next;
	}
	return (cmd);
}

void	add_cmd(t_cmd **cmd, t_data *data)
{
	t_cmd	*last_node;
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return ;
	memset(node, 0, sizeof(t_cmd));
	node->outfile = -2;
	node->infile = -2;
	node->data = data;
	if (!(*cmd))
	{
		(*cmd) = node;
		return ;
	}
	else
	{
		last_node = last_cmd((*cmd));
		last_node->next = node;
		node->prev = last_node;
	}
}

int	param_length(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		if (token && token->type != PIPE && token->type > 5)
		{
			if (token->type == CMD || token->type == ARG || token->type == VAR)
				i++;
		}
		if (token->type == PIPE)
			break ;
		token = token->next;
	}
	return (i);
}

char	**get_param(t_token *token)
{
	char	**param;
	int		i;

	i = 0;
	param = malloc(sizeof(char *) * (param_length(token) + 1));
	if (!param)
		return (NULL);
	while (token)
	{
		if (token && token->type != PIPE && token->type > 5)
		{
			if (token->type == CMD || token->type == ARG || token->type == VAR)
			{
				param[i] = token->str;
				i++;
			}
		}
		if (token->type == PIPE)
			break ;
		token = token->next;
	}
	param[i] = NULL;
	return (param);
}

void	init_heredoc(t_data *data)
{
	data->skip_q = false;
	data->exit_code = g_exit_codes;
	if (g_exit_codes == 130)
	{
		data->exit_code = g_exit_codes;
		g_exit_codes = 0;
	}
}
