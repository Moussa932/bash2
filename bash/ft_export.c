#include "minishell.h"

bool add_in_env(t_env **env, char *str)
{
    int i;
    bool equal;

    i = 0;
    equal = false;
    while (str[i] && str[i] != '=')
    {
        if (check_var_char(str[i]) == false)
            return false;
        i++;
        if (str[i] == '=')
            equal = true;
    }
    //if (!equal)
      //  return false;
    add_env(env, str);
    return true;
}

void printf_export(t_env **env, t_cmd *cmd, t_data *data)
{
    t_env *dup;

    //if (cmd -> outfile > 0)
      //  dup2(cmd -> outfile, STDOUT_FILENO);
    dup = (*env);
    while(dup)
    {
        printf("export %s\n", dup -> str);
        dup = dup -> next;
    }
    //dup2(data -> save_stdout, STDOUT_FILENO);
}

bool param_valid(char *str)
{
    int i;
    bool equal;

    equal = true;
    i = 0;
    while (str[i] && str[i] != '-')
    {
        i++;
        if (str[i] == '=' && str[i + 1] == '=')
            break;
        if (str[i] == '=')
            equal = true;
    }
    if (i == 0)
        return false;
    if (isalpha(str[0]) == 0 && str[0] != '_' && str[0] != '$')
    {
        ft_putstr_fd("error param syntax\n", 2);
        return false;
    }
    return equal;    
}



int ft_export(t_cmd *cmd, t_data *data, int index)
{
    int i;
    t_env *envi;

    envi = data -> envlist;
    i = 0;
    if (!param_valid(cmd -> param[index]))
    {
        //ft_putstr_fd("error param syntax\n", 2);
        return (1);
    }
    i = var_exist(cmd -> param[index], &envi);
    if (i > -1)
        update_env(&envi, i, cmd -> param[index]);
    else
        add_in_env(&envi, cmd -> param[index]);
    return (0);
}

int export_all(t_cmd *cmd, t_data *data)
{
    int i;
    int exit;
    int save_exit;

    if (ft_strncmp(cmd -> param[0], "export", 6) == 0 && !cmd -> param[1])
    {
        printf_export(&data -> envlist, cmd, data);
        return 0;
    }
    i = 1;
    save_exit = 0;
    while(cmd -> param[i])
    {
        exit = ft_export(cmd, data, i);
        if (exit == 1)
            save_exit = exit;
        i++;
    }
    return save_exit;
}