
#include "minishell.h"

// remove all the muliple psaces to keep one space only
char *remove_double_space(char *line)
{
    char    *resu;
    int	    i;
    int     j;

	i = ft_strlen(line) + 1;
	resu = malloc(i * sizeof(char *));
	ft_bzero(resu, i);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i + 1] != ' ')
		{
			resu[j] = line[i];
			j++;
		}
		i++;
	}
	return (resu);
}

// count the commands, possible problem with the redirection without space
int count_cmd(char *line)
{
    int count;
    int i;

    i = 0;
    count = 0;
    while (line[i])
    {
        if (line[i] == '\'')
        {
            i++;
            while(line[i] != '\'')
                i++;
        }
        else if (line[i] == '"')
        {
            i++;
            while(line[i] != '"')
                i++;
        }
        else if (line[i] == ' ')
            count++;
        i++;
    }
    return (count + 1);
}
// trasform the char* in char** delimited by space
char **pre_split(char *line)
{
    int     index;
    int     i;
    int     j;
    char    **resu;

    resu = malloc((count_cmd(line) + 1) * sizeof(char *));
    i = 0;
    j = 0;
    index = 0;
    while (line[i])
    {
        if (line[i] == '\'')
        {
            resu[index][j] = line[i];
            i++;
            j++;
            while(line[i] != '\'')
            {
                resu[index][j] = line[i];
                j++;
                i++;
            }
            resu[index][j] = line[i];
        }
        else if (line[i] == '"')
        {
            resu[index][j] = line[i];
            i++;
            j++;
            while(line[i] != '"')
            {
                resu[index][j] = line[i];
                j++;
                i++;
            }
            resu[index][j] = line[i];
        }
        else if (line[i] == ' ')
        {
            j = 0;
            index++;
        }
        else
        {
            resu[index][j] = line[i];
            j++;
        }
        i++;
    }
    return (resu);
}

// transform the command from char* to t_cmd type
int count_redir(char **list, char c)
{
    int i;
    int resu;

    i = 0;
    resu = 0;
    while(list[i])
    {
        if(list[i][0] == c)
            resu++;
        i++;
    }
    return (resu);
}

t_cmd   *alloc_cmd(char **list)
{
    t_cmd   *resu;
    int     i;
    int     j;
    int     k;

    i = count_redir(list, '<');
    j = count_redir(list, '>');
    resu = malloc(sizeof(t_cmd *));
    resu->stdin = malloc((i + 1) * sizeof(char *));
    resu->stdout = malloc((j + 1) * sizeof(char *));
    resu->cmd = malloc((tablen(list) - i - j + 1) * sizeof(char *));
    i = 0;
    j = 0;
    while (list[i])
    {
        if (list[i][0] == '<')
        {
            resu->stdin[j] = ft_strdup(list[i]);
            resu->stdin[j + 1] = ft_strdup(list[i + 1]);
            j = j + 2;
            k = i;
            while (list[k])
            {
                free(list[k]);
                list[k] = list[k + 2]; // put 2 null at the end of list
                k++;
            }
        }
        i++;
    }
    i = 0;
    j = 0;
    while (list[i])
    {
        if (list[i][0] == '>')
        {
            resu->stdout[j] = ft_strdup(list[i]);
            resu->stdout[j + 1] = ft_strdup(list[i + 1]);
            j = j + 2;
            k = i;
            while (list[k])
            {
                free(list[k]);
                list[k] = list[k + 2]; // put 2 null at the end of list
                k++;
            }
        }
        i++;
    }
    i = 0;
    j = 0;
    while (list[i])
    {
        resu->cmd[j] = ft_strdup(list[i]);
        i++;
        j++;
    }
    return (resu);
}

t_cmd	*split_inst(char *temp)
{
	t_cmd	*resu;
	char	*tmpclean;
	char	**list;
	int		i;

    resu = NULL;
	i = ft_strlen(temp) + 1;
	tmpclean = malloc(i * sizeof(char *));
	ft_bzero(tmpclean, i);
	tmpclean = remove_double_space(temp);
    list = pre_split(tmpclean);
    resu = alloc_cmd(list);

	
	return (resu);
}

t_cmd	**spliter3(char **inst)
{
	t_cmd	**resu;
	char	**temp;
	int		i;

	i = 0;
	temp = malloc((tablen(inst) + 1) * sizeof(char *));
	resu = malloc((tablen(inst) + 1) * sizeof(t_cmd));
	while (inst[i])
	{
		temp[i] = ft_strtrim(inst[i], " ");
		i++;
	}
	temp[i] = NULL;
	i = 0;
	while (temp[i])
	{
		resu[i] = split_inst(temp[i]);
		free(temp[i]);
		i++;
	}
	return (resu);
}
