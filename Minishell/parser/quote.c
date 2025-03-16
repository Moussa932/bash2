/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:43:00 by modembel          #+#    #+#             */
/*   Updated: 2025/03/07 17:44:05 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_to_delete(char c, bool *skip, char *q)
{
	if (!*skip && (c == '\'' || c == '\"'))
	{
		*skip = true;
		*q = c;
		return (1);
	}
	else if (*skip && c == *q)
	{
		*skip = false;
		return (2);
	}
	else
		return (0);
}

char	*quote_handler(char *str)
{
	int		i;
	int		j;
	char	q;
	char	*dest;
	bool	skip;

	i = 0;
	j = 0;
	q = 0;
	dest = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!dest)
		return (NULL);
	skip = false;
	while (str[i])
	{
		if (!quote_to_delete(str[i], &skip, &q))
			dest[j++] = str[i];
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

void	quote_destroyer(t_token *token)
{
	t_token	*tok;
	char	*tmp;

	tok = token;
	while (tok)
	{
		if (tok->quote == SQUOTE || tok->quote == DQUOTE)
		{
			tmp = tok->str;
			tok->str = quote_handler(tok->str);
			free(tmp);
		}
		tok = tok->next;
	}
}

void	set_quote(t_token *token)
{
	t_token	*tok;
	int		i;

	tok = token;
	while (tok)
	{
		i = 0;
		while (tok->str[i])
		{
			if (tok->str[i] == '\'')
			{
				tok->quote = SQUOTE;
				break ;
			}
			else if (tok->str[i] == '\"')
			{
				tok->quote = DQUOTE;
				break ;
			}
			i++;
		}
		tok = tok->next;
	}
}

bool	check_end(char *str, t_data *data)
{
	int		i;
	char	c;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			data->end_quote = false;
			c = str[i];
			while (str[++i])
			{
				if (str[i] == c)
				{
					data->end_quote = true;
					break ;
				}
			}
		}
		if (!str[i])
			break ;
	}
	return (data->end_quote);
}
