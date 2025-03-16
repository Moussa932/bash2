/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:35:12 by modembel          #+#    #+#             */
/*   Updated: 2025/03/03 07:26:11 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*last_env(t_env *env)
{
	while (env)
	{
		if (env != NULL && env->next == NULL)
			return (env);
		env = env->next;
	}
	return (env);
}

void	add_env(t_env **env, char *str)
{
	t_env	*last_node;
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	memset(node, 0, sizeof(t_env));
	node->free = false;
	node->str = str;
	if (!(*env))
	{
		*env = node;
		return ;
	}
	else
		last_node = last_env((*env));
	last_node->next = node;
	node->prev = last_node;
}

void	init_env(char **arg, t_env **env)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		add_env(env, arg[i]);
		i++;
	}
}

int	var_exist(char *str, t_env **env)
{
	int		i;
	int		size;
	t_env	*envi;

	i = 0;
	size = 0;
	envi = (*env);
	while (str[size])
	{
		if (str[size] == '=')
			break ;
		size++;
	}
	while (envi)
	{
		if (ft_strncmp(envi->str, str, size) == 0)
			return (i);
		i++;
		envi = envi->next;
	}
	return (-1);
}

void	update_env(t_env **env, int index, char *str)
{
	int		i;
	t_env	*dup;

	dup = (*env);
	i = 0;
	if (index == -1)
		return ;
	while (dup && i <= index)
	{
		if (i == index)
		{
			dup->str = ft_strdup(str);
			dup->free = true;
		}
		dup = dup->next;
		i++;
	}
}
