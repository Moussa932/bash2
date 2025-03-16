/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:34:20 by cfakoube          #+#    #+#             */
/*   Updated: 2025/03/09 10:13:51 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_env(t_env *envi, char *var)
{
	int		size;
	int		len;
	t_env	*env;

	env = envi;
	len = 0;
	size = ft_strlen(var);
	while (env)
	{
		if (ft_strncmp(env->str, var, size) == 0)
		{
			while (env->str[len] && env->str[len] != '=')
				len++;
			return (ft_strdup(env->str + len + 1));
		}
		env = env->next;
	}
	return (NULL);
}

char	*update_string(char *str, char *replace, char *var, int index)
{
	int		size;
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = ft_strlen(str) - (ft_strlen(var) + 1) + ft_strlen(replace);
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
			i += seconde_update_string(&j, dest, replace, var);
		if (!str[i])
			break ;
		dest[j] = str[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*before_dollar(char *str)
{
	int		i;
	char	*dest;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	dest = malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '$')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*special_cases(char *copy, char *var, int index)
{
	char	*replace;
	char	*str;

	if (var[0] == '?')
		replace = ft_itoa(g_exit_codes);
	else
		replace = ft_itoa(getpid());
	str = update_string(copy, replace, var, index);
	free(replace);
	free(var);
	free(copy);
	return (str);
}
