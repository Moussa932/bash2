/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:36:54 by modembel          #+#    #+#             */
/*   Updated: 2025/03/03 05:56:14 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	belong_to_env(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] == '=')
			return (false);
		if (str[i] == '=')
			break ;
		i++;
	}
	if (i == ft_strlen(str) || str[i + 1] == '\0')
		return (false);
	return (true);
}

int	ft_env(t_cmd *cmd, t_data *data)
{
	t_env	*envi;
	char	*path;

	envi = data->envlist;
	path = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	if (cmd->param[1] != NULL)
	{
		printf("error to many argument\n");
		return (1);
	}
	while (envi)
	{
		if (envi->str != NULL && ft_strncmp(envi->str, path, INT_MAX) != 0
			&& belong_to_env(envi->str))
			printf("%s\n", envi->str);
		envi = envi->next;
	}
	return (0);
}

char	**copy_arg_env(t_data *data)
{
	int		i;
	t_env	*env;
	char	**dest;

	i = 0;
	env = data->envlist;
	while (env)
	{
		env = env->next;
		i++;
	}
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (NULL);
	env = data->envlist;
	i = 0;
	while (env)
	{
		dest[i] = ft_strdup(env->str);
		i++;
		env = env->next;
	}
	dest[i] = NULL;
	return (dest);
}
