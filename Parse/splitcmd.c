/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:56:36 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/09 13:12:11 by rdi-marz         ###   ########.fr       */
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

// transform the command from char** to t_cmd type +25 lignes
t_cmd	*alloc_cmd(char **list)
{
	t_cmd	*resu;
	int		i;
	int		index[3];

	resu = ft_malloc_resu(list);
	i = 0;
	index[0] = 0;
	index[1] = 0;
	index[2] = 0;
	while (list[i])
	{
		if (list[i][0] == '<')
		{
			resu->stdin[index[0]++] = ft_strdup(list[i++]);
			if (list[i] != NULL)
				resu->stdin[index[0]++] = ft_strdup(list[i++]);
		}
		else if (list[i][0] == '>')
		{
			resu->stdout[index[1]++] = ft_strdup(list[i++]);
			if (list[i] != NULL)
				resu->stdout[index[1]++] = ft_strdup(list[i++]);
		}
		else
			resu->cmd[index[2]++] = ft_strdup(list[i++]);
	}
	return (resu);
}

t_cmd	*split_inst(char *temp)
{
	t_cmd	*resu;
	char	*tmpclean;
	char	**list;

	resu = NULL;
	tmpclean = remove_double_space(temp);
	list = pre_split(tmpclean);
	free(tmpclean);
	resu = alloc_cmd(list);
	free_tab(list);
	return (resu);
}

// + 25 lignes
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
	if (inst == NULL)
		return (NULL);
	while (inst[i])
	{
		temp[i] = ft_strtrim(inst[i], " ");
		tempclean[i] = ft_space_bracket(temp[i]);
		resu[i] = split_inst(tempclean[i]);
		free(tempclean[i++]);
	}
	free_tab(inst);
	free_tab(temp);
	free(tempclean);
	resu[i] = NULL;
	resu = validation_cmd(resu);
	return (resu);
}
// potentiel bug a cause de resu dans le resultat et les parametre
