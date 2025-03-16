/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:39:17 by modembel          #+#    #+#             */
/*   Updated: 2025/03/07 22:11:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	special_case(char **str, char *copy, char *var)
{
	if (*str[0] == '$')
		*str = ft_strdup("");
	else if (*str[0] != '$')
		*str = before_dollar(*str);
	free(var);
	free(copy);
}

void	clean_expansion(char *var, char *replace, char *copy)
{
	free(var);
	free(replace);
	free(copy);
}

int	seconde_update_string(int *j, char *dest, char *replace, char *var)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (replace[k])
	{
		dest[*j] = replace[k];
		k++;
		(*j)++;
	}
	i = ft_strlen(var) + 1;
	return (i);
}

int	env_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
