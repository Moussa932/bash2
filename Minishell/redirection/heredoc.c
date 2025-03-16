/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfakoube <cfakoube@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:44:36 by modembel          #+#    #+#             */
/*   Updated: 2025/03/09 11:30:58 by cfakoube         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*special_casess(char *copy, char *var, int index, int exit_c)
{
	char	*replace;
	char	*str;

	if (var[0] == '?')
		replace = ft_itoa(exit_c);
	else
		replace = ft_itoa(getpid());
	str = update_string(copy, replace, var, index);
	free(replace);
	free(var);
	free(copy);
	return (str);
}

void	set_var_valueee(char **str, t_env *env, int index, t_data *data)
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
		*str = special_casess(copy, var, index, data->exit_code);
	else if (!var_in_env(var, env) && var[0])
	{
		replace = ft_strdup("");
		*str = update_string(copy, replace, var, index);
		clean_expansion(var, replace, copy);
		data->skip_q = true;
	}
}

void	write_in_heredoc(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	if (line)
		free(line);
}

bool	get_line(int fd, char *delimiter, t_env *env, t_data *data)
{
	char	*line;
	int		i;

	init_heredoc(data);
	while (1)
	{
		if (g_exit_codes == 130)
			return (false);
		line = readline("heredoc>");
		if (!line)
			return (true);
		if (ft_strncmp(line, delimiter, INT_MAX) == 0)
			break ;
		i = 0;
		while (line[i])
		{
			data->skip_q = false;
			if (line[i] == '$' && line[i + 1])
				set_var_valueee(&line, env, i, data);
			if (!(line[i] && data->skip_q && line[i] == '$'))
				i++;
		}
		write_in_heredoc(fd, line);
	}
	return (true);
}

int	set_heredoc(char *str, t_data *data)
{
	char	*delimiter;
	int		fd;
	t_env	*env;

	env = data->envlist;
	delimiter = str;
	fd = open("heredoc_tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (fd);
	if (!get_line(fd, delimiter, env, data))
		data->cancel = true;
	close(fd);
	fd = open("heredoc_tmp.txt", O_RDONLY, 0644);
	if (fd > 0)
		unlink("heredoc_tmp.txt");
	return (fd);
}
