/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:56:36 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/19 23:36:47 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// transform the char* in char** delimited by space
char	**pre_split(char *line)
{
	int		index;
	int		i;
	int		j;
	char	**resu;

	resu = ft_init_resu(line);
	i = 0;
	j = 0;
	index = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			ft_copy_inside_simple_cote(&(resu[index]), line, &i, &j);
		else if (line[i] == '"')
			ft_copy_inside_double_cote(&(resu[index]), line, &i, &j);
		else if (line[i] == ' ')
		{
			j = 0;
			index++;
		}
		else
			resu[index][j++] = line[i];
		i++;
	}
	return (resu);
}

//  < a1 <  b2>   c3 ls | <"f6"  ls -la > g7>k8 | grep -v 'to | ta' >l9

// transform the command from char** to t_cmd type
t_cmd	*alloc_cmd(char **list)
{
	t_cmd	*resu;
	int		i;
	int		j;
	int		k;

	resu = ft_malloc_resu(list);
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
	tmpclean = ft_test(ft_calloc(i, sizeof(*tmpclean)), NULL);
	tmpclean = remove_double_space(temp);
	list = pre_split(tmpclean);
	resu = alloc_cmd(list);
	return (resu);
}

//  < a1 <  b2>   c3 ls | <"f6"  ls -la > g7>k8 | grep -v 'to | ta' >l9
t_cmd	**spliter3(char **inst)
{
	t_cmd	**resu;
	char	**temp;
	char	**tempclean;
	int		i;

	i = 0;
	temp = ft_test(ft_calloc((tablen(inst) + 1), sizeof(*temp)), NULL);
	tempclean = ft_test(ft_calloc((tablen(inst) + 1), sizeof(*temp)), NULL);
	resu = ft_test(ft_calloc((tablen(inst) + 1), sizeof(*resu)), NULL);
	while (inst[i])
	{
		temp[i] = ft_strtrim(inst[i], " ");
		tempclean[i] = ft_space_bracket(temp[i]);
		resu[i] = split_inst(tempclean[i]);
		i++;
	}
	temp[i] = NULL;
	tempclean[i] = NULL;
	resu[i] = NULL;
	return (resu);
}
