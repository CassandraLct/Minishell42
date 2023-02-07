/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:56:36 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/06 13:58:51 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// check if in0 is < or << and in1 not NULL and not < > << >> |
int	check_in(char *in0, char *in1)
{
	if (!in0 || !in1)
		return (1);
	if ((in0[0] == '<' && in1 == NULL) || (in0[0] == '>' && in1 == NULL))
	{
		printf(ERR_TOKEN);
		g_mini.ret_err = 258;
		return (0);
	}	
	if ((in0[0] == '<' || in0[0] == '>') && (in1[0] == '<' || in1[0] == '>'))
	{
		printf(ERR_TOKEN_SHORT);
		printf("%s'\n", in1);
		g_mini.ret_err = 258;
		return (0);
	}
	return (1);
}

// check some bad instructions or redirections
t_cmd	**validation_cmd(t_cmd **resu)
{
	int	i;
	int	j;

	i = 0;
	while (resu[i])
	{
		j = 0;
		while (resu[i]->cmd[j])
		{
			if ((check_in(resu[i]->stdin[j], resu[i]->stdin[j + 1]) == 0))
			{
				// leaks => free resu
				return (NULL);
			}
			if ((check_in(resu[i]->stdout[j], resu[i]->stdout[j + 1]) == 0))
			{
				// leaks => free resu
				return (NULL);
			}
			j++;
		}
		
		i++;
	}
	return (resu);
}
