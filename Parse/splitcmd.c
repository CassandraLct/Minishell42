
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
    list = malloc((count_cmd(tmpclean) + 1) * sizeof(char *)); // possible double malloc

	while(tmpclean[i])
	{
        list[i] =
	}
    free(list);
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
