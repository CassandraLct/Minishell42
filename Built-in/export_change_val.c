/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_change_val.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:03:34 by clecat            #+#    #+#             */
/*   Updated: 2022/12/08 17:13:28 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//recupere le nom de la variable
char	*recup_name(char *cmp, char *name_var)
{
	int	i;

	i = 0;
	if (check_var(cmp) == 1)
	{
		while (cmp[i] != '=')
		{
			name_var[i] = cmp[i];
			i++;
		}
		name_var[i] = '\0';
		if (cmp[i] != '\0')
			i++;
		i = 0;
	}
	else if (check_var(cmp) == 0)
	{
		while (cmp[i])
		{
			name_var[i] = cmp[i];
			i++;
		}
		name_var[i] = '\0';
	}
	return (name_var);
}
