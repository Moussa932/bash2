#include "minishell.h"

t_cmd *last_cmd(t_cmd *cmd)
{
    while (cmd)
    {
        if (cmd != NULL && cmd -> next == NULL)
            return cmd;
        cmd = cmd -> next;
    }
    return cmd;
}

void add_cmd(t_cmd **cmd, t_data *data)
{
    t_cmd *last_node;
    t_cmd *node;

    node = malloc(sizeof(t_cmd));
    if (!node)
        return ;
    memset(node, 0, sizeof(t_cmd));
    node -> outfile = -2;
    node -> infile = -2;
    node -> data = data;
    if (!(*cmd))
    {
        //printf("la valeur\n ");
        (*cmd) = node;
        return ;
    }
    else
    {
        last_node = last_cmd((*cmd));
        last_node -> next = node;
        node -> prev = last_node;
    }
    //return node;
}

int param_length(t_token *token)
{
    int i;

    i = 0;
    while(token)
    {
        if (token && token -> type != PIPE && token -> type > 5)
        {
        //printf("HAHA BATARD\n");
            if (token -> type == CMD || token -> type == ARG || token -> type == VAR)
                i++;
        /*if (token -> next == NULL)
            break;*/
        }
        if (token -> type == PIPE)
            break;
        token = token -> next;
    }
    return (i);
}