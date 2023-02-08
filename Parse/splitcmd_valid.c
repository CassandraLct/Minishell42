/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:56:36 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/08 17:09:37 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check the Valdity of Redirections,
// if in0 is < << > >> and in1 not NULL and not < > << >> | then return 1
int	cvr(char *in0, char *in1)
{
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
	while (resu[i])
	{
		j = 0;
		while (j <= g_mini.nb_cmd)
		{
			if ((resu[i]->stdin[j] && resu[i]->stdin[j + 1]
					&& (cvr(resu[i]->stdin[j], resu[i]->stdin[j + 1]) == 0))
				|| (resu[i]->stdout[j] && resu[i]->stdout[j + 1]
					&& (cvr(resu[i]->stdout[j], resu[i]->stdout[j + 1]) == 0)))
			{
//				free_t_cmd(resu); LEAKS
				return (NULL);
			}
			j++;
		}
		i++;
	}
	return (resu);
}
