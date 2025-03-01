#include "minishell.h"

void close_fd(t_cmd *command, t_cmd *actual_fd)
{

    while (command)
    {
        if (command != actual_fd)
        {
            close(command -> fd[0]);
            close(command -> fd[1]);
        }
        command = command -> next;
    }
}

void set_pipe(t_cmd *cmd, t_cmd *command)
{
    if (cmd -> infile > -1)   //NOT FINISH ONLY IF PIPE HAS BEEN INIT
    {
        dup2(cmd ->infile, STDIN_FILENO);
        cmd -> fd[0] = cmd -> infile;
    }
    else if (cmd && cmd -> prev)
        dup2(cmd -> prev -> fd[0], STDIN_FILENO);
    if (cmd && cmd -> next)
        dup2(cmd -> fd[1], STDOUT_FILENO);
    
    close_fd(command, cmd);
}




int child_process(t_cmd *command, t_data *data)
{
    char *cmd_path;
    int exit_c;
    char **path_env;
    char *cmd;

    path_env = NULL;
    cmd = NULL;
    set_pipe(command, data -> cmd);
    child_signal();
    if (identifie_builtin(command -> param[0]) == 0)
    {
        exit_c = start_builtins(data, command);
        close(command -> fd[0]);
        close(command -> fd[1]);
        free_all(data);
        exit(exit_c);
    }
    cmd_path = set_path_cmd(command, data, &path_env, &cmd);
    if (ft_strncmp(command -> param[0], "cat", 3) == 0 && command -> outfile > 0)
        dup2(command -> outfile, STDOUT_FILENO);
    if (command -> outfile > 0)
        dup2(command -> outfile, STDOUT_FILENO);
    if (execve(cmd_path, command -> param, data -> env) == -1)
    {
        //dup2(STDERR_FILENO, STDOUT_FILENO);
        //printf("%s\n", strerror(errno));
        free_path_error(path_env, cmd, command, 2); // REWORK ERR 
    }
    
    close(command -> fd[0]);
    close(command -> fd[1]);
    free_all(data);
    exit(0);
}