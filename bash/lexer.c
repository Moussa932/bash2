#include "minishell.h"

int exit_codes = 0;

int length_command(char *line)
{
    int i;
    bool quote;

    quote = false;
    i = 0;
    while (line[i] && !is_space(line[i]) && !is_token(line[i]))
    {
        if (line[i] == '"' || line[i] == '\'')
        {
           i++;
           while (line[i])
           {
                while (line[i] != '"' && line[i] != '\'' && line[i] && line[i] != ' ')
                    i++;
                if (line[i] == '"' || line[i] == '\'')
                    quote = true;
                if (end_token(line, i, quote))
                    return i;
                i++;
           }
        }
        if (!line[i])
          break;
        i++;
    }
    return (i);
}

void *string_management(char *s, int *i,t_token **token)
{
    int end;
    char *dest;
    int k;
    t_token *last;

    k = 0;
    end = length_command(s);
    dest = malloc(sizeof(char) * end + 1);
    if (!dest)
        return NULL;
    while (k < end)
    {
        dest[k] = s[k];
        k++;
    }
    dest[k] = '\0';
    add_token(token, CMD, dest, i);
    last = ft_last((*token));
    if (last-> prev == NULL || last -> prev -> type == PIPE)
        last -> type = CMD;
    else
        last -> type = ARG;
}

void identifie_token(char *line, int *i, t_token **token)
{
    char *s;
    s = line + *i;
    if (ft_strncmp(s, "<<", 2)== 0)
        add_token(token, HEREDOC, ft_strdup("<<"),i);
    else if (ft_strncmp(s, ">>", 2) == 0)
        add_token(token, APPEND, ft_strdup(">>"),i);
    else if (ft_strncmp(s, ">", 1) == 0)
        add_token(token, TRUNC, ft_strdup(">"),i);
    else if (ft_strncmp(s, "<" , 1) == 0)
        add_token(token, INPUT, ft_strdup("<"), i);
    else if (ft_strncmp(s, "|", 1)== 0)
        add_token(token, PIPE, ft_strdup("|"), i);
    else
        string_management(s, i, token);  
}

void lexer_expander(t_token *token, char *line, t_data *data)
{
    int i;
    
    i = 0;

    while (line[i])
    {
        while (line[i] && is_space(line[i]) == true)
            i++;
        if (line[i] == '\0')
            break;
        identifie_token(line, &i, &token);
    }
    set_quote(token);
    set_var(token);
    quote_destroyer(token);
    data -> token = token;
    var_expansion(data);
}

bool check_line(char *s, t_data  *data, char **tmp)
{
    int i;

    i = 0;
    if (!s)
    {
        data -> tmps = tmp;
        exit_shell(data, exit_codes, 1);
    }
    while (s[i] && is_space(s[i]))
        i++;
    if (i == ft_strlen(s))
    {
        free_all(data);
        return false;
    }
    if (!check_end(s, data))
    {
        ft_putstr_fd("error quote\n", 2);
        free_all(data);
        return false;
    }
    return true;
}

char **no_env()
{
    char buff[PATH_MAX];
    char **arg;

    getcwd(buff,PATH_MAX);
    arg = malloc(sizeof(char *) * 4 + 1);
    arg[0] = ft_strjoin("PWD=", buff);
    arg[1] = "SHLVL=1";
    arg[2] = "_=/usr/bin/env";
    arg[3] = "PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
    arg[4] = NULL;

    return arg;
}
         
//gcc ft_exit.c exit_shell.c expanser.c expanser_utils.c signal.c lexer.c lexer_utils.c libc.c quote.c export_utils.c heredoc.c command.c command_utils.c exec2.c exec.c ft_cd.c free.c ft_echo.c ft_env.c ft_export.c ft_pwd.c ft_unset.c path_cmd.c -lreadline -g
//valgrind --leak-check=full --show-leak-kinds=all --suppressions=ignore.txt ./a.out echo "$cat lol.c | cat >lol.c"
char **check_env(char **env, t_data *data)
{
    data -> env_unset = false;
    if (!env[0])
    {
        data -> env_unset = true;
        return no_env();
    }
    return env;
}

void data_init(t_data *data, char **env)
{
    memset(data, 0, sizeof(t_data));
    data -> env = check_env(env, data);
    data -> cancel = false;
    data -> end_quote = true;
    init_env(data -> env, &data -> envlist);
    data -> save_stdin = dup(STDIN_FILENO);
    data -> save_stdout = dup(STDOUT_FILENO);
}

int main(int argc, char **argv, char **env)
{
    t_data data;
    char **tmp;

    tmp = NULL;
    set_signal();
    while(1)
    {
        data_init(&data, env);
        data.line = readline("minishell>");
        add_history(data.line);                                                           ///REWORK EXPORT QUOTE EXIT 126 heredoc '$'
        if (!check_line(data.line, &data, tmp))
            continue;
        data.tmps = tmp;
        lexer_expander(data.token, data.line, &data);
        if(create_command(&data))
            exec(&data, data.cmd);
        env = copy_arg_env(&data);
        free_all(&data);
        if (data.line)
            free(data.line);
        tmp = env;
    }   
}