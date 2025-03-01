#include "minishell.h"

int ft_pwd(t_cmd *cmd)
{
    char buff[PATH_MAX];

    if (cmd -> param[1] != NULL)
    {
        ft_putstr_fd("pwd: too many arguments\n", 2);
        return 1;
    }
    if (getcwd(buff, PATH_MAX))
    {
        printf("%s\n", buff);
        //exit(0);
        return 0;
    }
    else
    {
        ft_putstr_fd("pwd\n", 2);
        return 1;
    }
    //exit(0);
}