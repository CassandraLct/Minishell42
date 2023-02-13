/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:56:36 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/13 11:16:22 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//3fonctions
// Check the Valdity of Redirections IN,
// if in0 is < << > >> and in1 not NULL and not < > << >> | then return 1
int	cvrin(t_cmd **resu, int i, int *j)
{
	char	*in0;
	char	*in1;

	in0 = resu[i]->stdin[*j];
	in1 = resu[i]->stdin[*j + 1];
	*j += 2;
	if ((in0[0] == '<' && in1 == NULL) || (in0[0] == '>' && in1 == NULL))
	{
		write(2, ERR_TOKEN, ft_strlen(ERR_TOKEN));
		g_mini.ret_err = 258;
		return (0);
	}	
	if ((in0[0] == '<' || in0[0] == '>') && (in1[0] == '<' || in1[0] == '>'))
	{
		ft_print_error_msg3(ERR_TOKEN_SHORT, in1, "'\n");
		g_mini.ret_err = 258;
		return (g_mini.ret_err);
	}
	return (1);
}

// Check the Valdity of Redirections out,
// if in0 is < << > >> and in1 not NULL and not < > << >> | then return 1
int	cvrout(t_cmd **resu, int i, int *j)
{
	char	*in0;
	char	*in1;

	in0 = resu[i]->stdout[*j];
	in1 = resu[i]->stdout[*j + 1];
	*j += 2;
	if ((in0[0] == '<' && in1 == NULL) || (in0[0] == '>' && in1 == NULL))
	{
		write(2, ERR_TOKEN, ft_strlen(ERR_TOKEN));
		g_mini.ret_err = 258;
		return (0);
	}	
	if ((in0[0] == '<' || in0[0] == '>') && (in1[0] == '<' || in1[0] == '>'))
	{
		ft_print_error_msg3(ERR_TOKEN_SHORT, in1, "'\n");
		g_mini.ret_err = 258;
		return (g_mini.ret_err);
	}
	return (1);
}

// check some bad instructions or redirections +25 lignes
t_cmd	**validation_cmd(t_cmd **resu)
{
	int	i;
	int	j;
	int	not_err;

	i = 0;
	not_err = 1;
	while (i < g_mini.nb_cmd)
	{
		j = 0;
		while (resu[i]->stdin[j])
			not_err = cvrin(resu, i, &j);
		j = 0;
		while (resu[i]->stdout[j])
			not_err = cvrout(resu, i, &j);
		i++;
	}
	if (not_err == 0)
	{
		free_t_cmd(resu);
		return (NULL);
	}
	return (resu);
}
