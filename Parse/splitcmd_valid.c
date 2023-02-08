/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:56:36 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/08 15:19:40 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// check if in0 is < or << and in1 not NULL and not < > << >> |
int	check_in(char *in0, char *in1)
{
	if ((in0[0] == '<' && in1 == NULL) || (in0[0] == '>' && in1 == NULL))
	{
		printf(ERR_TOKEN);
		g_mini.ret_err = 258;
		printf("sortie 1\n");
		return (0);
	}	
	if ((in0[0] == '<' || in0[0] == '>') && (in1[0] == '<' || in1[0] == '>'))
	{
		printf(ERR_TOKEN_SHORT);
		printf("%s'\n", in1);
		g_mini.ret_err = 258;
		printf("sortie 2\n");
		return (0);
	}
	printf("sortir de checkin\n");
	return (1);
}

// check some bad instructions or redirections
t_cmd	**validation_cmd(t_cmd **resu)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (resu[0]->cmd[j])
	{
		printf("cmd[j] = {%s}\n", resu[0]->cmd[j]);
		if (resu[0]->cmd[j] == NULL)
			printf("cmd NULL\n");
		else if (resu[0]->cmd[j] == 0)
			printf("cmd egale 0\n");
		j++;
	}
	j = 0;
	// while(resu[0]->stdin[j]) //n'est pas print
	// 	printf("cmd[j] = %s\n", resu[0]->stdin[j++]);
	// i = 0;
	// while(resu[0]->stdout[j]) //n'est pas print
	// 	printf("cmd[j] = %s\n", resu[0]->stdout[j++]);
	printf("entrer de validation_cmd\n");
	while (resu[i])
	{
		j = 0;
		while (j <= g_mini.nb_cmd)
		{
			if (resu[i]->stdin[j] && resu[i]->stdin[j + 1]
				&& (check_in(resu[i]->stdin[j], resu[i]->stdin[j + 1]) == 0))
			{
				// leaks => free resu
				return (NULL);
			}
			if (resu[i]->stdout[j] && resu[i]->stdout[j + 1]
				&& (check_in(resu[i]->stdout[j], resu[i]->stdout[j + 1]) == 0))
			{
				// leaks => free resu
				return (NULL);
			}
			j++;
		}
		i++;
	}
	printf("sortie de validation_cmd\n");
	return (resu);
}
