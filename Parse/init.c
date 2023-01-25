/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:36:33 by clecat            #+#    #+#             */
/*   Updated: 2023/01/25 10:27:46 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//5 fonctions
void	aff_err(char **cmd)
{
	if (check_arg(cmd[1]) == 1)
		printf("minishell: cd: %s: Not a directory\n", cmd[1]);
	else
	{
		printf("minishell: cd: %s: ", cmd[1]);
		printf("No such file or directory\n");
	}
	g_mini.ret_err = 1;
}

//initialise la structure
void	init_struct(t_min *mini, char **envp)
{
	mini->ret_err = 0;
	mini->line = NULL;
	mini->tab = NULL;
	mini->prompt = "minishell> ";
	mini->c_env = ft_cpytab(envp);
	init_export(mini);
	mini->nb_passage_exp = 0;
	mini->val_home = recup_valhome(mini->c_env);
}

//creer la copie d'export au tout début
void	init_export(t_min *mini)
{
	mini->c_exp = init_exp(mini->c_env);
	mini->c_exp = order_exp(mini->c_exp, mini->c_env);
}

//free les tableaux etc
void	free_all(t_min mini)
{
	free_tab(mini.c_env);
	free_tab(mini.c_exp);
	free(mini.val_home);
}

//recup valeur home pour cd et ~
char	*recup_valhome(char	**c_env)
{
	char	*tmp;
	int		i;
	int		j;
	int		y;

	i = 0;
	j = 0;
	y = 0;
	while (c_env[i++])
	{
		if (ft_strncmp(c_env[i], "HOME=", 5) == 0)
			break ;
	}
	tmp = malloc(sizeof(char) * (ft_strlen(c_env[i])));
	while (c_env[i][j] != '=')
		j++;
	j += 1;
	while (c_env[i][j])
	{
		tmp[y] = c_env[i][j];
		j++;
		y++;
	}
	tmp[y] = '\0';
	return (tmp);
}
