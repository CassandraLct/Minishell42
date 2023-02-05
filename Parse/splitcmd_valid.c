/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:56:36 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/02 12:50:25 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check some bad instructions or redirections
t_cmd	**validation_cmd(t_cmd **resu)
{
	int	i;
	int	j;

	i = 0;
	dprintf(2, "ici\n");
	while(resu[i])
	{
		j = 0;
		while(resu[i]->stdin[j])
		{
			if ((resu[i]->stdin[j][0] == '<' && resu[i]->stdin[j + 1] == NULL)
				|| (resu[i]->stdout[j][0] == '>' && resu[i]->stdout[j + 1] == NULL))
			{
				printf(ERR_TOKEN);
				g_mini.ret_err = 2; // ??
				exit (2);
			}
			j++;
		}
	}
	return (resu);
}

/*
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
		free(inst[i]);
		tempclean[i] = ft_space_bracket(temp[i]);
		free(temp[i]);
		resu[i] = split_inst(tempclean[i]);
		free(tempclean[i++]);
	}
	free(inst);
	free(temp);
	free(tempclean);
	resu[i] = NULL;
	return (resu);
}
*/