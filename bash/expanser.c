#include "minishell.h"

char *copy_env(t_env **env, char *var)
{
    int i;
    int size;
    int len;

    i = -1;
    len = 0;
    size = ft_strlen(var);
    while ((*env))
    {
        if (ft_strncmp((*env) -> str, var, size) == 0)
        {
            while((*env) -> str[len] && (*env) -> str[len] != '=')
                len++;
            return (ft_strdup((*env) -> str + len + 1));
        }
        (*env) = (*env) -> next;
    }
    return NULL;
}

int seconde_update_string(int *j, char *dest, char *replace, char *var)
{
    int k;

    k = 0;
    int i = 0;
    while (replace[k])
    {
        dest[*j] = replace[k];
        k++;
        (*j)++;
    }
    i = ft_strlen(var) + 1;
    return i;
}

char *update_string(char *str, char *replace, char *var, int index)
{
    int size;
    char *dest;
    int i;
    int j;
    
    i = 0;
    j = 0;
    size = ft_strlen(str) - (ft_strlen(var) + 1) + ft_strlen(replace);
    dest = malloc(sizeof(char) * size + 1);
    if (!dest)
        return NULL;
    while (str[i])
    {
        if (str[i] == '$' && i == index)
            i += seconde_update_string(&j, dest, replace, var);
        if (!str[i])
            break;
            dest[j] = str[i];
        i++;
        j++;
    }
    dest[j] = '\0';
    return dest; 
}

char *before_dollar(char *str)
{
    int i;
    char *dest;

    i = 0;
    while(str[i] && str[i] != '$')
        i++;
    dest = malloc(sizeof(char) * i + 1);
    if(!dest)
        return NULL;
    i = 0;
    while (str[i] && str[i] != '$')
    {
        dest[i] = str[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}
void special_case(char **str, char *copy, char *var)
{
    if (*str[0] == '$')
        *str = ft_strdup("");
    else if (*str[0] != '$')
    *str = before_dollar(*str);
    free(var);
    free(copy);
}

void clean_expansion(char *var, char *replace, char *copy)
{
    free(var);
    free(replace);
    free(copy);
}

void set_var_value(char **str, t_env **env, int index, int exit_code)
{
    char *var;
    char *replace;
    char *copy;

    copy = *str;
    var = var_isolation(copy, index);
    if (var_in_env(var, env))
    {
        replace = copy_env(env, var);
        *str = update_string(copy, replace, var, index);
        clean_expansion(var, replace, copy);
    }
    else if (var[0] == '?' || var[0] == '$')
    {
        if (var[0] == '?')
            replace = ft_itoa(exit_codes);
        else 
            replace = ft_itoa(getpid());
        *str = update_string(copy, replace, var, index);
        clean_expansion(var, replace, copy);
    }
    else if (!var_in_env(var, env))  //error "$ PATH" shoud free var if !var[0]
        special_case(str, copy, var);
}




void var_expansion(t_data *data)
{
    t_token *tok;
    int i;
    t_env *envi;

    tok = data -> token;
    envi = data -> envlist;
    while (tok)
    {
        i = -1;
        if (tok -> type == VAR  && tok -> quote != SQUOTE)
        {
            while (tok -> str[++i])
            {
                if (tok -> str[i] == '$' && tok -> str[i + 1])
                    set_var_value(&tok -> str, &envi, i, data -> exit_code);
                if (!tok -> str[i])
                    break;
            }
        }
        tok = tok -> next;
    }
}
