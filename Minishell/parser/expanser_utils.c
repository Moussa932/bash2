/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:34:54 by cfakoube          #+#    #+#             */
/*   Updated: 2025/03/09 11:47:59 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_var(t_token *token)
{
	t_token	*tok;
	int		i;

	tok = token;
	while (tok)
	{
		i = -1;
		while (tok->str[++i])
		{
			if (tok->str[i] == '$' && ft_strlen(tok->str) > 1)
				tok->type = VAR;
		}
		tok = tok->next;
	}
}

bool	check_var_char(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	return (true);
}

void	set_var_range(int *start, int *end, char *str, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			i = i + 1;
			break ;
		}
		i++;
	}
	*start = i;
	while (str[i])
	{
		if (check_var_char(str[i]) == false)
			break ;
		j++;
		i++;
	}
	*end = j;
}

char	*var_isolation(char *str, int index)
{
	int		start;
	int		end;
	char	*var;

	if (str[index + 1] == '?' || str[index + 1] == '$')
	{
		var = ft_substr(str, index + 1, 1);
		return (var);
	}
	set_var_range(&start, &end, str, index);
	var = ft_substr(str, start, end);
	return (var);
}

bool	var_in_env(char *str, t_env *envi)
{
	t_env	*env;

	env = envi;
	while (env)
	{
		if (env->str && ft_strncmp(env->str, str, env_size(env->str)) == 0
			&& ft_strlen(str) == env_size(env->str))
			return (true);
		env = env->next;
	}
	return (false);
}
