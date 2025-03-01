#include "minishell.h"

void set_var(t_token *token)
{
    t_token *tok;
    tok = token;
    int i;
    
    while (tok)
    {
        i = -1;
        while (tok -> str[++i])
        {
            if (tok -> str[i] == '$' && ft_strlen(tok -> str) > 1)
                tok -> type = VAR;
        }
        
        tok = tok -> next;
    }
}

bool check_var_char(char c)
{
    if (ft_isalnum(c) == 0 && c != '_')
        return false;
    return true;
}


void set_var_range(int *start, int *end, char *str, int index)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(str[i])
    {
        if (str[i] == '$' && i == index)
        {
            i = i + 1;
            break;
        }
        i++;
    }
    *start = i;
    while (str[i])
    {
        if (check_var_char(str[i]) == false)
            break;
        j++;
        i++;
    }
    *end = j;
}

char *var_isolation(char *str, int index)
{
    int start;
    int end;
    char *var;
    if (str[index + 1] == '?' || str[index + 1] == '$')
    {
        var = ft_substr(str, index + 1, 1);
        return var;
    }
    set_var_range(&start, &end, str, index);
    var = ft_substr(str, start, end);
    return var;
}

bool var_in_env(char *str, t_env **env)
{
    int size;

    size = ft_strlen(str);
    while ((*env))
    {
        if ((*env) -> str && ft_strncmp((*env) -> str, str, size) == 0)
            return true;
        (*env) = (*env) -> next;
    }
    return false;
}