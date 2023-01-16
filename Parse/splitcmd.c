#include "minishell.h"

char	*remove_double_space(char *line)
{
	char	*resu;
	int		i;
	int		j;

	i = ft_strlen(line) + 1;
	resu = malloc(i * sizeof(char *));
	ft_bzero(resu, i);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (!(line[i] == ' ' && line[i + 1] == ' '))
		{
			resu[j] = line[i];
			j++;
		}
		i++;
	}
	return (resu);
}

// count the commands, possible problem with the redirection without space
int	count_cmd(char *line)
{
    int	count;
    int	i;
    
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
char	**pre_split(char *line)
{
    int		index;
    int		i;
    int		j;
    char	**resu;

    i = count_cmd(line) + 1;
    resu = malloc(i * sizeof(char *));
    index = 0;
    j = ft_strlen(line) + 1;
    printf("pre_split\n");
    while(index < i - 1)
    {
        resu[index] = malloc(j * sizeof(char *));
        ft_bzero((void *)resu[index], j);
        printf("resu[%d]=[%s] ", index, resu[index]);
        index++;
    }
    printf("\n");
    resu[index] = NULL;
    i = 0;
    j = 0;
    index = 0;
    printf("pre_split suite\n");
    while (line[i])
    {
//        printf("pre_split, i=%d    ", i);
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
            printf("space, resu[%d]=[%s]\n", index, resu[index]);
            index++;
        }
        else
        {
//            printf("line[%d]=%c\n", i, line[i]);
            resu[index][j] = line[i];
            j++;
        }
        i++;
    }
    printf("end, resu[%d]=[%s]\n", index, resu[index]);
    printf("end, resu[%d]=[%s]\n", index + 1, resu[index + 1]);
    return (resu);
}

// count the number of redirection defined in ched c
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

// transform the command from char** to t_cmd type
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
    ft_bzero((void *)resu->stdin, i + 1); // size ?
    resu->stdout = malloc((j + 1) * sizeof(char *));
    ft_bzero((void *)resu->stdout, j + 1); // size ?
    resu->cmd = malloc((tablen(list) - i - j + 1) * sizeof(char *));
    ft_bzero((void *)resu->cmd, tablen(list) - i - j + 1); // size ?
    // test
    i = 0;
    while(list[i])
    {
        printf("list[%d]=[%s] ", i , list[i]);
        i++;
    }
    printf("list[%d]=[%s] \n", i ,list[i]);
    // end test
    i = 0;
    j = 0;
    while (list[i])
    {
        printf("redir in, i=[%d], list[%d]=[%s], list[%d]=[%s] \n", i, i, list[i], i + 1, list[i + 1]);
        if (list[i][0] == '<')
        {
            resu->stdin[j] = ft_strdup(list[i]);
            resu->stdin[j + 1] = ft_strdup(list[i + 1]);
            resu->stdin[j + 2] = NULL; // to remove if bzero ok
            printf("list[%d]=[%s] list[%d]=[%s]\n", i, list[i], i + 1, list[i + 1]);
            printf("resu->stdin[%d]=[%s] resu->stdin[%d]=[%s]\n", j, resu->stdin[j], j + 1, resu->stdin[j + 1]);
            j = j + 2;
            k = i;
            while (list[k])
            {
//                free(list[k]);
                list[k] = list[k + 2]; // put 2 null at the end of list ?
                k++;
            }
            // test
            k = 0;
            printf("---after removing redir in --->");
            while(list[k])
            {
                printf("list[%d]=[%s] ", k , list[k]);
                k++;
            }
            printf("list[%d]=[%s] \n", k ,list[k]);
            // end test
            i--;
        }
        i++;
    }
    i = 0;
    j = 0;
    while (list[i])
    {
        printf("redir out, i=[%d]\n", i);
        if (list[i][0] == '>')
        {
            resu->stdout[j] = ft_strdup(list[i]);
            resu->stdout[j + 1] = ft_strdup(list[i + 1]);
            resu->stdout[j + 2] = NULL; // to remove if bzero ok
            printf("list[%d]=[%s] list[%d]=[%s]\n", i, list[i], i + 1, list[i + 1]);
            printf("resu->stdout[%d]=[%s] resu->stdout[%d]=[%s]\n", j, resu->stdout[j], j + 1, resu->stdout[j + 1]);
            j = j + 2;
            k = i;
            while (list[k])
            {
//                free(list[k]);
                list[k] = list[k + 2]; // put 2 null at the end of list ?
                k++;
            }
            // test
            k = 0;
            printf("---after removing redir out --->");
            while(list[k])
            {
                printf("list[%d]=[%s] ", k , list[k]);
                k++;
            }
            printf("list[%d]=[%s] \n", k ,list[k]);
            // end test
            i--;
        }
        i++;
    }
    i = 0;
    j = 0;
    while (list[i])
    {
        resu->cmd[j] = ft_strdup(list[i]);
        resu->cmd[j + 1] = NULL;
        printf("list[%d]=[%s]\n", j, list[j]);
        printf("resu->cmd[%d]=[%s]\n", j, resu->cmd[j]);
        i++;
        j++;
    }
    printf("end of alloc\n");
    return (resu);
}

t_cmd   *split_inst(char *temp)
{
	t_cmd   *resu;
	char    *tmpclean;
	char    **list;
	int     i;

    resu = NULL;
	i = ft_strlen(temp) + 1;
	tmpclean = malloc(i * sizeof(char *));
	ft_bzero(tmpclean, i);
	tmpclean = remove_double_space(temp);
    printf("split_inst, after remove double space\n");
    printf("tmpclean=[%s]\n", tmpclean);
    list = pre_split(tmpclean);
    printf("split_inst, after pre split\n");
    resu = alloc_cmd(list);
    printf("split_inst, after alloc_cmd\n");
	return (resu);
}

// < a1 <  b2 >   c3 > d4  ls | < e5 < f6  ls  > g7 >  k8
t_cmd   **spliter3(char **inst)
{
	t_cmd	**resu;
	char	**temp;
	int		i;

	i = 0;
    printf("tablen(inst)=%d\n", tablen(inst));
	temp = malloc((tablen(inst) + 1) * sizeof(char *));
	resu = malloc((tablen(inst) + 1) * sizeof(t_cmd));
	while (inst[i])
	{
        printf("spliter3, inst[%d]=[%s]\n", i, inst[i]);
        temp[i] = ft_strtrim(inst[i], " ");
        printf("spliter3, temp[%d]=[%s]\n", i, temp[i]);
        // ajouter ici le traitement de < et > sans espace
        i++;
	}
    printf("spliter3, out of first while\n");
	temp[i] = NULL;
	i = 0;
	while (temp[i])
	{
        printf("spliter3, processing resu[%d]...\n", i);
        resu[i] = split_inst(temp[i]);
	//	free(temp[i]);
		i++;
	}
    resu[i] = NULL;
    printf("spliter3, out of second while\n");
	return (resu);
}
