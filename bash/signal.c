#include "minishell.h"

void sighandler()
{
    printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
    exit_codes = 130;
}

void set_signal()
{
    signal(SIGINT, &sighandler);
    signal(SIGQUIT, SIG_IGN);
    //signal(SIGTSTP, SIG_IGN);
}

void quit_handler()
{
    //dup2(STDERR_FILENO, STDOUT_FILENO);
    printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
    exit_codes = 131;
}

void child_signal()
{
    signal(SIGQUIT, &quit_handler);
}

/*void sigheredoc()
{
    printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
    global = 1;
}

int heredoc_signal()
{
    signal(SIGINT, &sigheredoc);
}*/

