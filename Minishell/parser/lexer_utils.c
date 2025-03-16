/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:40:32 by modembel          #+#    #+#             */
/*   Updated: 2025/03/03 07:15:16 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_last(t_token *token)
{
	if (!token)
		return (NULL);
	while (token != NULL)
	{
		if (token != NULL && token->next == NULL)
			return (token);
		token = token->next;
	}
	return (token);
}

void	add_token(t_token **token, int type, char *s, int *i)
{
	t_token	*node;
	t_token	*last_node;

	node = malloc(sizeof(t_token));
	if (!node)
		return ;
	memset(node, 0, sizeof(t_token));
	*i = *i + ft_strlen(s);
	node->type = type;
	node->quote = NQUOTE;
	node->str = s;
	if ((*token) == NULL)
	{
		(*token) = node;
		return ;
	}
	else
	{
		last_node = ft_last(*token);
		last_node->next = node;
		node->prev = last_node;
	}
}

bool	is_space(char s)
{
	if (s == ' ' || (s >= 9 && s <= 13))
		return (true);
	return (false);
}

bool	is_token(char s)
{
	if (s == '<' || s == '>' || s == '|')
		return (true);
	return (false);
}

bool	end_token(char *line, int i, bool quote)
{
	if (line[i] == ' ' && quote != false)
		return (true);
	return (false);
}
