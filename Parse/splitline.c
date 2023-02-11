/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/11 16:22:24 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//2 fonctions
// main loop of spliter / +25lignes(printf)
char	**spliter_loop(char **resu, char *temp)
{
	int		inb;
	int		j;
	int		k;

	inb = 0;
	j = 0;
	k = 0;
	while (g_mini.line[j])
	{
		if (is_single_pipe(j) == 1)
		{
			resu[inb++] = ft_strdup(temp);
			k = 0;
		}
		else
		{
			temp[k] = g_mini.line[j];
			temp[++k] = '\0';
		}
		j++;
	}
	resu[inb] = ft_strdup(temp);
	resu[inb + 1] = NULL;
	return (resu);
}

//line too long = printf l.69, l.70, l.72
// cut the line received from readline, the separator are real pipes 
char	**spliter(void)
{
	char	**resu;
	char	*temp;

	resu = NULL;
	temp = NULL;
	if (iscotevalid(g_mini.line) == 0)
	{
		printf("minishell: quote not closed\n");
		return (NULL);
	}
	g_mini.nb_cmd = count_instruct(g_mini.line);
	resu = ft_test(ft_calloc(g_mini.nb_cmd + 1, sizeof(*resu)), NULL);
	temp = ft_test(ft_calloc(ft_strlen(g_mini.line) + 1, sizeof(*temp)), NULL);
	resu = spliter_loop(resu, temp);
	free(temp);
	return (resu);
}
