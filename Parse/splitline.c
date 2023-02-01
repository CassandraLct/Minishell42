/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitline.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:01:25 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/01 14:50:46 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// main loop of spliter / +25lignes(printf)
char	**spliter_loop(char **resu, char *temp)
{
	int		inb;
	int		j;
	int		k;

	inb = 0;
	j = 0;
	k = 0;
	// printf("g_mini,line = %s\n", g_mini.line);
	while (g_mini.line[j])
	{
		// printf("dans le while, ret = %d\n", is_single_pipe(j));
		// printf("g_mini.line[j] = %c\n", g_mini.line[j]);
		if (is_single_pipe(j) == 1)
		{
			// printf("dans le if, temp = %s\n", temp);
			// free(resu[inb]);
			resu[inb++] = ft_strdup(temp);
			k = 0;
		}
		else
		{
			// printf("dans le else\n");
			temp[k] = g_mini.line[j];
			// printf("temp[k] = %c, g_mini.line = %c\n", temp[k], g_mini.line[j]);
			temp[++k] = '\0';
		}
		j++;
	}
	// free(resu[inb]);
	// printf("temp = %s, %d\n", temp, ft_strlen(temp));
	resu[inb] = ft_strdup(temp);
	resu[inb + 1] = NULL;
	return (resu);
}

//line too long = printf l.69, l.70, l.72
// cut the line received from readline, the separator are real pipes 
char	**spliter(void)
{
	char	**resu;
	int		i;
	char	*temp;

	resu = NULL;
	temp = NULL;
	if (iscotevalid(g_mini.line) == 0)
	{
		printf("minishell: cote not closed\n");
		return (NULL);
	}
	i = count_instruct(g_mini.line);
	resu = ft_test(ft_calloc(i + 1, sizeof(ft_strlen(g_mini.line))), NULL);
//	printf("strlenline = %d, strlen(temp)= %d\n", ft_strlen(g_mini.line), ft_strlen(temp));
	temp = ft_test(ft_calloc(ft_strlen(g_mini.line) + 1, sizeof(*temp)), NULL);
//	dprintf(2, "strlenline = %d, strlen(temp)= %d\n", ft_strlen(g_mini.line), ft_strlen(temp));
	// printf("avant split_loop\n");
	resu = spliter_loop(resu, temp);
	// printf("apres spliter_loop\n");
	free(temp);
	// printf("fin spliter\n");
	return (resu);
}
