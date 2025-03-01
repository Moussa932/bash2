#include "minishell.h"

void exit_shell(t_data *data, int ex_code, int ctrl_d)
{
    /*char **tmp;
    int i;

    i = 0;
    tmp = data -> tmps;
    if (tmp)
    {
        while(tmp[i])
        {
            free(tmp[i]);
            i++;
        }
        free(tmp);
    }*/
    if (ctrl_d == 1)
        ft_putstr_fd("exit\n", 1);
    free_all(data);
    exit(ex_code);
}