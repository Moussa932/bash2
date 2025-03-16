/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:27:48 by cfakoube          #+#    #+#             */
/*   Updated: 2024/05/27 16:12:02 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list		*bloc;

	bloc = malloc(sizeof(t_list));
	if (bloc == NULL)
		return (NULL);
	bloc->content = content;
	bloc->next = NULL;
	return (bloc);
}
