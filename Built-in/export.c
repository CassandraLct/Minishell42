/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:06:38 by clecat            #+#    #+#             */
/*   Updated: 2022/11/15 10:54:54 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Pour export affiche que certaine 
ecrit delare-x avant le nom de la variable, mets entre cote ce qu'il y a après le =
affiche les variables par ordre ascii
export (qqc) sans égale s'affcihe que dans export
si = afficher aussi dans env*/

void	export(g_min mini)
{
	int	i;
	int	j;
	char index = 33;
	
	i = 0;
	while(mini.c_env[i])
	{
		printf("dans while c_env de i\n");
		if(mini.c_env[i][0] == index || mini.c_env[j][0] == index)
		{
			printf("env[i] = %s, env[j] = %s\n", mini.c_env[i], mini.c_env[j]);
			if(strcmp(&mini.c_env[i][0], &mini.c_env[j][0]) == -1)
			{
				printf("declare -x");
				printf("%s\n", mini.c_env[i]);
			}
			else if(strcmp(&mini.c_env[i][0], &mini.c_env[j][0]) == 1)
			{
				printf("declare -x");
				printf("%s\n", mini.c_env[j]);
			}
			j = i + 1;
		}
		index++;
		i++;
	}
}

/*int	main(void)
{
	g_min mini;

	export(mini);
}*/