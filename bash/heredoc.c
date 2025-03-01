#include "minishell.h"

bool get_line(int fd, char *delimiter, t_data *data, t_env *env)
{
    char *line;
    int i;
    
    while (1)
    {
        line = readline("heredoc>");
        if (!line)
            return true;
        if (exit_codes == 130)
            return false;
        if (ft_strncmp(line, delimiter, INT_MAX) == 0)
            break;
        i = 0;
        while (line[i])
        {
            if (line[i] == '$' && line[i + 1])
                set_var_value(&line, &env, i, data -> exit_code);
            if (!line[i])
                break;
            i++;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        if (line)
            free(line);
    }
    return true;
}

int set_heredoc(char *str, t_cmd *cmd, t_data *data)
{
    char *delimiter;
    int fd;
    t_env *env;

    env = data -> envlist;
    delimiter = str;
    fd = open("heredoc_tmp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
        return fd;
    if (!get_line(fd, delimiter, data, env))
        data -> cancel = true;
    fd = open("heredoc_tmp.txt", O_RDONLY, 0644);
    if(fd > 0)
        unlink("heredoc_tmp.txt");
    return fd;
}