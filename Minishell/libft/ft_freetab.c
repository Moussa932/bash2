/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 03:30:07 by root              #+#    #+#             */
/*   Updated: 2024/10/26 01:09:47 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freetab(char **strs)
{
	int	j;

	j = 0;
	if (strs == NULL)
		return ;
	while (strs[j])
		ft_free(strs[j++]);
	ft_free(strs);
}
