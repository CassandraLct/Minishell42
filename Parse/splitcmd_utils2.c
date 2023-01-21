/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 10:56:36 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/21 12:00:20 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// initialise the variable resu in pre_split
char	**ft_init_resu(char *line)
{
	char	**resu;
	int		index;
	int		i;
	int		j;

	i = count_cmd(line) + 1;
	j = ft_strlen(line) + 1;
	resu = ft_test(ft_calloc(i, sizeof(*resu)), NULL);
	index = 0;
	while (index < i - 1)
	{
		resu[index] = ft_test(ft_calloc(j, sizeof(*resu[index])), NULL);
		index++;
	}
	resu[index] = NULL;
	return (resu);
}

// copy what is inside the simple cote
void	ft_copy_inside_simple_cote(char **res, char *line, int *i, int *j)
{
	printf("res=[%s]. line =[%s], i=[%d], j=[%d]\n", *res, line, *i, *j);
	(*res)[(*j)++] = line[(*i)++];
	while (line[*i] != '\'')
		(*res)[(*j)++] = line[(*i)++];
	(*res)[*j] = line[*i];
	(*res)[*j + 1] = '\0';
}

// copy what is inside the double cote
void	ft_copy_inside_double_cote(char **res, char *line, int *i, int *j)
{
	(*res)[(*j)++] = line[(*i)++];
	while (line[*i] != '"')
		(*res)[(*j)++] = line[(*i)++];
	(*res)[*j] = line[*i];
	(*res)[*j + 1] = '\0';
}

// malloc the structure that contains all the redir and cmd
t_cmd	*ft_malloc_resu(char **list)
{
	int		i;
	int		j;
	int		k;
	t_cmd	*resu;

	i = count_redir(list, '<');
	j = count_redir(list, '>');
	k = tablen(list) + 1;
	resu = ft_test(ft_calloc(1, sizeof(*resu)), NULL);
	resu->stdin = ft_test(ft_calloc(2 * i + 1, sizeof(*resu->stdin)), NULL);
	resu->stdout = ft_test(ft_calloc(2 * j + 1, sizeof(*resu->stdout)), NULL);
	resu->cmd = ft_test(ft_calloc(k, sizeof(*resu->cmd)), NULL);
	return (resu);
}

// free the t_cmd struct after each line
// void	free_t_cmd(void)
// {
// 	int	i;

// 	i = 0;
// }