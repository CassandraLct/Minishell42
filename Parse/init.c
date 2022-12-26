/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:36:33 by clecat            #+#    #+#             */
/*   Updated: 2022/12/26 10:23:17 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
}

//creer la copie d'export au tout début
void	init_export(t_min *mini)
{
	int	i;

	i = 0;
	mini->c_exp = init_exp(mini->c_env);
	mini->c_exp = order_exp(mini->c_exp, mini->c_env);
}

void	free_all(t_min mini)
{
	free_tab(mini.c_env);
	free_tab(mini.c_exp);
}
