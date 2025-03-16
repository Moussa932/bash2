/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:42:20 by modembel          #+#    #+#             */
/*   Updated: 2025/03/09 17:54:32 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	length_command(char *line)
{
	int		i;
	char	c;

	i = 0;
	while (line[i] && !is_space(line[i]) && !is_token(line[i]))
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			c = line[i++];
			while (line[i] != c)
				i++;
		}
		if (!line[i])
			break ;
		i++;
	}
	return (i);
}

void	*string_management(char *s, int *i, t_token **token)
{
	int		end;
	char	*dest;
	int		k;
	t_token	*last;

	k = 0;
	end = length_command(s);
	dest = malloc(sizeof(char) * end + 1);
	if (!dest)
		return (NULL);
	while (k < end)
	{
		dest[k] = s[k];
		k++;
	}
	dest[k] = '\0';
	add_token(token, CMD, dest, i);
	last = ft_last((*token));
	if (last->prev == NULL || last->prev->type == PIPE)
		last->type = CMD;
	else
		last->type = ARG;
	return (NULL);
}

void	identifie_token(char *line, int *i, t_token **token)
{
	char	*s;

	s = line + *i;
	if (ft_strncmp(s, "<<", 2) == 0)
		add_token(token, HEREDOC, ft_strdup("<<"), i);
	else if (ft_strncmp(s, ">>", 2) == 0)
		add_token(token, APPEND, ft_strdup(">>"), i);
	else if (ft_strncmp(s, ">", 1) == 0)
		add_token(token, TRUNC, ft_strdup(">"), i);
	else if (ft_strncmp(s, "<", 1) == 0)
		add_token(token, INPUT, ft_strdup("<"), i);
	else if (ft_strncmp(s, "|", 1) == 0)
		add_token(token, PIPE, ft_strdup("|"), i);
	else
		string_management(s, i, token);
}

void	lexer_expander(t_token *token, char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] && is_space(line[i]) == true)
			i++;
		if (line[i] == '\0')
			break ;
		identifie_token(line, &i, &token);
	}
	set_var(token);
	data->token = token;
	var_expansion(data);
	set_quote(token);
	quote_destroyer(token);
}

void	ft_close(int fd)
{
	if (fd <= 2)
		return ;
	close(fd);
}
