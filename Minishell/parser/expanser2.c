/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modembel <modembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 22:14:41 by root              #+#    #+#             */
/*   Updated: 2025/03/15 19:02:48 by modembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_var_value(char **str, t_env *env, int index)
{
	char	*var;
	char	*replace;
	char	*copy;

	copy = *str;
	var = var_isolation(copy, index);
	if (ft_strlen(var) < 1)
		return (free(var));
	if (var_in_env(var, env))
	{
		replace = copy_env(env, var);
		*str = update_string(copy, replace, var, index);
		clean_expansion(var, replace, copy);
	}
	else if (var[0] == '?' || var[0] == '$')
		*str = special_cases(copy, var, index);
	else if (!var_in_env(var, env) && var[0])
	{
		replace = ft_strdup("");
		*str = update_string(copy, replace, var, index);
		clean_expansion(var, replace, copy);
	}
}

void	set_var_valuee(char **str, t_env *env, int index, bool *skip)
{
	char	*var;
	char	*replace;
	char	*copy;

	copy = *str;
	var = var_isolation(copy, index);
	if (ft_strlen(var) < 1)
		return (free(var));
	if (var_in_env(var, env))
	{
		replace = copy_env(env, var);
		*str = update_string(copy, replace, var, index);
		clean_expansion(var, replace, copy);
	}
	else if (var[0] == '?' || var[0] == '$')
		*str = special_cases(copy, var, index);
	else if (!var_in_env(var, env) && var[0])
	{
		replace = ft_strdup("");
		*str = update_string(copy, replace, var, index);
		clean_expansion(var, replace, copy);
		*skip = true;
	}
}

static int	for_the_norm(char c, bool q)
{
	if (q && (c == '\'' || (c == '\"' || (c == '$'))))
		return (1);
	return (0);
}

char	*var_expansion_two(char *str, t_data *data, int *i, bool *skip)
{
	int		j;
	char	c;
	char	*dest;

	j = *i;
	dest = str;
	if (dest[j] == '\'' || dest[j] == '\"')
	{
		c = dest[j];
		j++;
		while (dest[j] && dest[j] != c)
		{
			if (dest[j] == '$' && c != '\'')
				set_var_valuee(&dest, data->envlist, j, skip);
			if (*skip && dest[j] == '$')
				continue ;
			else
				j++;
		}
	}
	*i = j;
	return (dest);
}

void wave_to_home(t_token *token, t_env *envi)
{
	t_token *tok;
	t_env *env;
	int i;
	char *tmp;

	tok = token;
	env = envi;
	i = 0;
	tmp = NULL;
	while (tok)
	{
		if (ft_strncmp(tok -> str, "~", ft_strlen(tok -> str)) == 0 && var_exist("HOME", &env) != -1)
		{
			while (i < var_exist("HOME", &env) && env)
				env = env -> next;
			tmp = tok -> str;
			tok -> str = ft_substr(env -> str, 5, ft_strlen(env -> str));
			free(tmp);
		}
		tok = tok -> next;
	}
}
void	var_expansion(t_data *data)
{
	t_token	*tok;
	int		i;
	bool	q;

	tok = data->token;
	while (tok)
	{
		i = 0;
		if (tok->type == VAR)
		{
			while (tok->str[i])
			{
				q = false;
				tok->str = var_expansion_two(tok->str, data, &i, &q);
				if (tok->str[i] == '$')
					set_var_valuee(&tok->str, data->envlist, i, &q);
				if (tok->str[i] && for_the_norm(tok->str[i], q) == 0)
					i++;
			}
		}
		tok = tok->next;
	}
	wave_to_home(data -> token, data -> envlist);
}




