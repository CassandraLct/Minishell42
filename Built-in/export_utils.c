/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:35:49 by clecat            #+#    #+#             */
/*   Updated: 2022/11/17 17:07:49 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//3 fonctions

//compare la taille des 2
int	tablen(t_min mini)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (mini.c_env[i])
		i++;
	while (mini.c_exp[y])
		y++;
	if (y != i)
		return (1);
	return (0);
}

//verifie si index envoyer est deja present dans copy exp
int	check_exp(t_min mini, int index)
{
	int	i;

	i = 0;
	while (mini.c_exp[i])
	{
		if (strcmp(mini.c_env[index], mini.c_exp[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

//copie env ds exp dans l'ordre ascii
void	fill_exp(t_min mini, char *str)
{
	int	i;

	i = 0;
	while (mini.c_exp[i])
		i++;
	mini.c_exp[i] = ft_strdup(str);
	mini.c_exp[i + 1] = NULL;
}
