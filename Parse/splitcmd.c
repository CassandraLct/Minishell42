/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:56:36 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/18 11:00:53 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_double_space(char *line)
{
	char	*resu;
	int		i;
	int		j;

	i = ft_strlen(line) + 1;
	resu = ft_calloc(i, sizeof(*resu));
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
			while (line[i] != '\'')
				i++;
		}
		else if (line[i] == '"')
		{
			i++;
			while (line[i] != '"')
				i++;
		}
		else if (line[i] == ' ')
			count++;
		i++;
	}
	return (count + 1);
}

// transform the char* in char** delimited by space
char	**pre_split(char *line)
{
	int		index;
	int		i;
	int		j;
	char	**resu;

	i = count_cmd(line) + 1;
	resu = ft_calloc(i, sizeof(*resu));
	index = 0;
	j = ft_strlen(line) + 1;
	while (index < i - 1)
	{
		resu[index] = ft_calloc(j, sizeof(*resu[index]));
		index++;
	}
	resu[index] = NULL;
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
			while (line[i] != '\'')
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
			while (line[i] != '"')
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

// count the number of redirection defined in ched c but also in cotes
// no bigdeal as the use is for malloc, bigger is not a problem
int	count_redir(char **list, char c)
{
	int	i;
	int	resu;

	i = 0;
	resu = 0;
	while (list[i])
	{
		if (list[i][0] == c)
			resu++;
		i++;
	}
	return (resu);
}

// transform the command from char** to t_cmd type
t_cmd	*alloc_cmd(char **list)
{
	t_cmd	*resu;
	int		i;
	int		j;
	int		k;

	i = count_redir(list, '<');
	j = count_redir(list, '>');
	resu = ft_calloc(1, sizeof(*resu));
	resu->stdin = ft_calloc(2 * i + 1, sizeof(*resu->stdin));
	resu->stdout = ft_calloc(2 * j + 1, sizeof(*resu->stdout));
	resu->cmd = ft_calloc((tablen(list) - i - j + 1), sizeof(*resu->cmd));
	i = 0;
	j = 0;
	while (list[i])
	{
		if (list[i][0] == '<')
		{
			resu->stdin[j] = ft_strdup(list[i]);
			resu->stdin[j + 1] = ft_strdup(list[i + 1]);
//			resu->stdin[j + 2] = NULL; // to remove if bzero ok
			j = j + 2;
			k = i;
			while (list[k])
			{
				//free(list[k]);
				list[k] = list[k + 2]; // put 2 null at the end of list ?
				k++;
			}
			i--;
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
			resu->stdout[j + 2] = NULL; // to remove if bzero ok
			j = j + 2;
			k = i;
			while (list[k])
			{
				//free(list[k]);
				list[k] = list[k + 2]; // put 2 null at the end of list ?
				k++;
			}
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
	tmpclean = ft_calloc(i, sizeof(*tmpclean));
	tmpclean = remove_double_space(temp);
	list = pre_split(tmpclean);
	resu = alloc_cmd(list);
	return (resu);
}

// count the number of > >> < or << even if in cotes
int	count_all_redir(char *temp)
{
	int	i;
	int	resu;

	i = 0;
	resu = 0;
	while (temp[i])
	{
		if (temp[i] == '>' && temp[i + 1] != '>')
			resu++;
		else if (temp[i] == '<' && temp[i + 1] != '>')
			resu++;
		i++;
	}
	return (resu);
}

char	*ft_space_bracket(char *s)
{
	char	*resu;
	int		i;
	int		k;

	i = 2 * count_all_redir(s) + 1;
	resu = ft_calloc((ft_strlen(s) + i), sizeof(*s));
	i = 0;
	k = 0;
	while (s[i])
	{
		if (i != 0 && s[i] == '>' && s[i - 1] != ' ' && s[i - 1] != '>')
		{
			resu[k] = ' ';
			k++;
		}
		if (i != 0 && s[i] == '<' && s[i - 1] != ' ' && s[i - 1] != '<')
		{
			resu[k] = ' ';
			k++;
		}
		resu[k] = s[i];
		k++;
		if (s[i + 1] && s[i] == '>' && s[i + 1] != ' ' && s[i + 1] != '>')
		{
			resu[k] = ' ';
			k++;
		}
		if (s[i + 1] && s[i] == '<' && s[i + 1] != ' ' && s[i + 1] != '<')
		{
			resu[k] = ' ';
			k++;
		}
		i++;
	}
	return (resu);
}

//  < a1 <  b2 >   c3 ls | < "f6"  ls -la > g7 >  k8 | grep -v 'to | ta' >l9
t_cmd	**spliter3(char **inst)
{
	t_cmd	**resu;
	char	**temp;
	char	**tempclean;
	int		i;

	i = 0;
	temp = ft_calloc((tablen(inst) + 1), sizeof(*temp));
	tempclean = ft_calloc((tablen(inst) + 1), sizeof(*temp));
	resu = ft_calloc((tablen(inst) + 1), sizeof(*resu));
	while (inst[i])
	{
		temp[i] = ft_strtrim(inst[i], " ");
		tempclean[i] = ft_space_bracket(temp[i]);
		i++;
	}
	temp[i] = NULL;
	tempclean[i] = NULL;
	i = 0;
	while (tempclean[i])
	{
		resu[i] = split_inst(tempclean[i]);
//		free(temp[i]);
		i++;
	}
	resu[i] = NULL;
	return (resu);
}
