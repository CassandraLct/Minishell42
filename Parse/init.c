/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:36:33 by clecat            #+#    #+#             */
/*   Updated: 2022/11/22 13:30:40 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//initialise la structure
t_min	init_struct(t_min mini, char **envp)
{
	mini.ret_err = 0;
	mini.prompt = "minishell>";
	mini.c_env = ft_cpytab(envp);
	mini.cdpath = ".";
	mini.c_exp = init_export(mini);
	return (mini);
}

//creer la copie d'export modifier order_exp
char	**init_export(t_min mini)
{
	mini.c_exp = init_exp(mini.c_env);
	order_exp(mini);
	return (mini.c_exp);
}
