#include "minishell.h"

char **get_param(t_cmd *cmd, t_token *token)
{
    char **param;
    int i;
    //t_token *leng;

    i = 0;
    //printf("%d\n",  param_length(token) + 1);
    //exit(0);
    param = malloc(sizeof(char *) * (param_length(token) + 1));
    if (!param)
        return NULL;
    while(token)
    {
        if (token && token -> type != PIPE && token -> type > 5)
        {
            if (token -> type == CMD || token -> type == ARG || token -> type == VAR)
            {
                //printf("%s\n %d\n",token -> str, token -> type);
                param[i] = token -> str; //param[i] = ft_strdup(token -> str);
                i++;
            }
         /*if (token -> next == NULL)
            break;*/
        }
        if (token -> type == PIPE)
            break;
        token = token -> next;
    }
    //exit(0);
    param[i] = NULL;
    return param;
}

bool get_outfile_fd(t_token *tok, t_cmd *cmd)
{
    char *str;

    if (cmd -> outfile >= 0)
        close(cmd -> outfile);
    if (!tok -> next || tok -> next -> type <= 5)
    {
        ft_putstr_fd("parse error\n", STDERR_FILENO);
        exit_codes = 2;
        return false;
    }
    str = tok -> next -> str;
    tok -> next -> type = ZERO;
    if (tok -> type == APPEND)
    cmd -> outfile = open(str, O_CREAT | O_WRONLY | O_APPEND, 0644);
    else
    cmd -> outfile = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (cmd -> outfile == -1)
    {
        printf("%s\n", strerror(errno));
        return (false);
    }
    return (true);
}


bool get_infile_fd(t_token *tok, t_cmd *cmd, t_data *data)
{
    char *str;
    if (cmd -> infile >= 0)
        close(cmd -> infile);
    if (!tok -> next || tok -> next -> type <= 5)
    {
        ft_putstr_fd("parse error\n", STDERR_FILENO);
        exit_codes = 2;
        return false;
    }
    str = tok -> next -> str;
    tok -> next -> type = ZERO;
    if (tok -> type == INPUT)
        cmd -> infile = open(str, O_RDONLY, 0644);
    else
        cmd -> infile = set_heredoc(str, cmd, data);
    if (cmd -> infile == -1)
    {
        printf("%s\n", strerror(errno));
        return (false);
    }
    return (true);
}

bool set_command(t_cmd **cmd, t_token *token, t_data *data)
{
    t_token *tok;
    t_cmd *command;

    tok = token;
    add_cmd(cmd, data);
    command = last_cmd((*cmd));
    //printf("%s et type [%d]", token -> str, token -> type);
    while (tok && tok -> type != PIPE )
    {
        //printf("ouais\n");
        if (tok -> type == APPEND || tok -> type == TRUNC)
        {
            if(!get_outfile_fd(tok, command))
                return false;
        }
        else if (tok -> type == HEREDOC || tok -> type == INPUT)
        {
                if(!get_infile_fd(tok, command, data))
                    return false;
        }
        tok = tok -> next;
    }
    command -> param = get_param((*cmd), token);
    return true;
}

bool create_command(t_data *data)
{
    t_cmd *cmd;
    t_token *token;
    bool succes;
    
    succes = true;
    cmd = data -> cmd;
    token = data -> token;
    if (token)
        if(!set_command(&cmd, token, data))
            succes = false;
    token = token -> next;
    while (token)
    {
        if (token -> prev -> type == PIPE)
            if(!set_command(&cmd, token , data))
                succes = false;
        token = token -> next;
    }
    data -> cmd = cmd;
    /*while (cmd)
    {
        int i = 0;
        while (cmd -> param[i])
        {
            printf("%s\n", cmd -> param[i]);
            i++;
        }
        printf("next\n");
        cmd = cmd -> next;
    }*/
    //exit(0);
    return succes;
}