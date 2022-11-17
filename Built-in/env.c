/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:05:50 by clecat            #+#    #+#             */
/*   Updated: 2022/11/17 16:40:15 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//1 fonctions
//a modifier : ne doit pas afficher les variables sans valeur
void	print_env(t_min mini)
{
	int	i;

	i = 0;
	while (mini.c_env[i])
	{
		printf("%s\n", mini.c_env[i]);
		i++;
	}
}
