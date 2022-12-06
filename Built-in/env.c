/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:05:50 by clecat            #+#    #+#             */
/*   Updated: 2022/12/06 15:34:01 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//1 fonctions
void	ft_env(t_min mini)
{
	int	i;

	i = 1;
	if (mini.tab[i] != NULL)
	{
		printf("env: %s: No such file or directory\n", mini.tab[i]);
		return ;
	}
	else
	{
		i = 0;
		while (mini.c_env[i])
		{
			printf("%s\n", mini.c_env[i]);
			i++;
		}
	}
}
