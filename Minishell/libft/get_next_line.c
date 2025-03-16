/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:04:30 by cfakoube          #+#    #+#             */
/*   Updated: 2024/11/02 23:44:41 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_pick_line(char *str)
{
	int		i;
	int		end;
	char	*s;

	i = 0;
	end = 0;
	s = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!s)
		return (0);
	while (str[i] && !end)
	{
		s[i] = str[i];
		if (s[i] == '\n')
			end = 1;
		i++;
	}
	s[i] = '\0';
	return (s);
}

static char	*ft_next_line(char *str)
{
	int		i;
	int		j;
	char	*new_tmp;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	new_tmp = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new_tmp)
		return (ft_free(str), NULL);
	j = 0;
	while (str[i])
		new_tmp[j++] = str[i++];
	new_tmp[j] = '\0';
	ft_free(str);
	return (new_tmp);
}

static int	ft_is_newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static void	ft_clean(char *tmp, char *line)
{
	ft_free(tmp);
	ft_free(line);
}

char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*line;
	char		*tmp2;
	int			octets_lus;

	if (fd < 0)
		return (ft_free(tmp), NULL);
	line = malloc(sizeof(char) * (1024 + 1));
	if (!line)
		return (NULL);
	octets_lus = 1024;
	while (!ft_is_newline(tmp) && octets_lus == 1024)
	{
		octets_lus = read(fd, line, 1024);
		if ((octets_lus < 0) || ((octets_lus == 0 && (!tmp || !*tmp))))
			return (ft_clean(tmp, line), tmp = NULL);
		line[octets_lus] = '\0';
		tmp2 = ft_strjoin(tmp, line);
		ft_free(tmp);
		tmp = tmp2;
	}
	ft_free(line);
	line = ft_pick_line(tmp);
	tmp = ft_next_line(tmp);
	return (line);
}
/*
int	main(int argc, char **argv)
{
	int		fd;
	char	*str;

	if (argc != 2)
		return (printf("Nombre d'arguments insuffisant"));
	fd = open(argv[1], O_RDONLY);
	while ((str = get_next_line(fd)))
	{
		printf("LIGNE AFFICHEE : %s\n", str);
		ft_free(str);
	}
	close(fd);
}*/