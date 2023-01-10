/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:21:09 by clecat            #+#    #+#             */
/*   Updated: 2023/01/10 16:41:10 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//fonction essaie
char	**gestion_cotes(t_min mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mini.line[i])
	{
		while (mini.line[i] != 32)
		{
			mini.tab[j][i] = mini.line[i];
		}
		i++;
	}
	return (mini.tab);
}

//+25lignes
//a finir (ne gere pas encore les cotes)
//a modifier (possiblement sous forme de boucle)
char	**split_line(t_min mini)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (mini.line[i])
	{
		if (mini.line[i] == 34 || mini.line[i] == 39)
		{
			while (mini.line[i++] != 34 || mini.line[i++] != 39)
			{
				j++;
				break ;
			}
		}
		i++;
	}
	if (j == 0)
		mini.tab = ft_split(mini.line, ' ');
	else
	{
		printf("ne pas split entre les cotes,redirection vers autre fonction\n");
		mini.tab = gestion_cotes(mini);
	}
	return (mini.tab);
}

//built-in : cd/echo/env/exit/export/unset
//redirige soit vers les built-in soit vers execve
void	redirection(t_min *mini)
{
	if (mini->tab[0] == NULL)
		return ;
	if (ft_strcmp(mini->tab[0], "exit") == 0)
		exit_min(mini);
	else if (ft_strcmp(mini->tab[0], "echo") == 0)
		echo(mini);
	else if (ft_strcmp(mini->tab[0], "env") == 0)
		ft_env(mini);
	else if (ft_strcmp(mini->tab[0], "cd") == 0)
		cd(mini);
	else if (ft_strcmp(mini->tab[0], "export") == 0)
		export(mini);
	else if (ft_strcmp(mini->tab[0], "unset") == 0)
		unset(mini);
	else if (ft_strcmp(mini->tab[0], "pwd") == 0)
		pwd(mini->c_env);
	else
		ft_set_pathexec(mini);
}
