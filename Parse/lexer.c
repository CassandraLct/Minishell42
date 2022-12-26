/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:21:09 by clecat            #+#    #+#             */
/*   Updated: 2022/12/26 10:59:40 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//a finir (ne gere pas encore les cotes)
//+25 lignes
char	**split_line(t_min mini)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (mini.line[i])
	{
		if (mini.line[i] == 34 || mini.line[i] == 39)
		{
			c = mini.line[i];
			while (mini.line[i] != 34 || mini.line[i] != 39)
			{
				printf("gestion des cotes\n");
				j++;
				i++;
			}
		}
		i++;
	}
	if (j == 0)
		mini.tab = ft_split(mini.line, ' ');
	return (mini.tab);
}

//built-in : cd/echo/env/exit/export/unset
//redirige soit vers les built-in soit vers execve
void	redirection(t_min *mini)
{
	if (mini->tab[0] == NULL)
		return ;
	if (strcmp(mini->tab[0], "exit") == 0)
		exit_min(mini);
	else if (strcmp(mini->tab[0], "echo") == 0)
		echo(mini);
	else if (strcmp(mini->tab[0], "env") == 0)
		ft_env(mini);
	else if (strcmp(mini->tab[0], "cd") == 0)
		cd(mini);
	else if (strcmp(mini->tab[0], "export") == 0)
		export(mini);
	else if (strcmp(mini->tab[0], "unset") == 0)
		unset(mini);
	else if (strcmp(mini->tab[0], "pwd") == 0)
		pwd(mini->c_env);
	else
		ft_set_pathexec(mini);
}
