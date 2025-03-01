#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * i + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char  *tmp_oldpwd()
{
	char buff[PATH_MAX];
	char *tmp;

	if(getcwd(buff, PATH_MAX))
		tmp = ft_strjoin("OLDPWD=", buff);
	//printf("tmp [%s]", tmp);
	return tmp;
}

int get_pwd(char *str, t_data *data, char *oldpwd)
{
    char buff[PATH_MAX];
    char *tmp;
	t_env *env;

	env = data -> envlist;
	data -> old_pwd = ft_strdup(oldpwd);
	update_env(&env,  var_exist("OLDPWD=", &env), oldpwd);
	if (var_exist("OLDPWD=", &env) == -1)
		add_env(&env, data -> old_pwd);
    if(!getcwd(buff, PATH_MAX))
    {
        printf("%s\n", strerror(errno));
        return -1;
    }
    tmp = ft_strjoin("PWD=", buff);
	data -> pwd = ft_strdup(tmp);
	update_env(&env, var_exist("PWD=", &env), tmp);
	if (var_exist("PWD=", &env) == -1)
		add_env(&env, data -> pwd);
	free(tmp);
	return 0;
}

char *get_home(t_data *data)
{
	t_env *env;
	int i;
	char *dest;

	dest = NULL;
	env = data -> envlist;
	while (env)
	{
		if (ft_strncmp(env -> str, "HOME", 4) == 0)
			dest = ft_substr(env -> str, 5, INT_MAX);
		env = env -> next;
	}
	if (!dest)
		ft_putstr_fd("HOME not set\n", 2);
	return dest;

}

int change_direc(t_cmd *cmd , t_data *data, char *home)
{
	if (cmd -> param[1] && cmd -> param[2])
	{
		ft_putstr_fd("cd: to many argument\n", 2);
		return 1;
	}
	if (!cmd -> param[1])
	{
		cmd -> param[1] = home;
		if(!cmd -> param[1])
			return 1;
	}
    if (chdir(cmd -> param[1]) == -1)
	{
		printf("%s\n",strerror(errno));
		return 1;
	}
}

int ft_cd(t_cmd *cmd, t_data *data) 
{
	char *str;

	str = tmp_oldpwd();
	data -> home = get_home(data);
	if (change_direc(cmd , data, data -> home) == 1)
	{
		if (data -> home)
			free(data -> home);
		free(str);
		return 1;
	}
    if (get_pwd(cmd -> param[1], data, str) == -1)
	{
		if (data -> home)
			free(data -> home);
		free(str);
		return 1;
	}
	if (data -> home)
		free(data -> home);
	free(str);
    return (0);
}