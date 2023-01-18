/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:59:04 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/01/17 21:59:17 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// used in ft_strstrim
static int	ft_isinlist(char c, char *list)
{
	int	i;

	i = 0;
	while (list[i] != '\0')
	{
		if (list[i] == c)
			return (1);
		i++;
	}
	return (0);
}

// used in ft_strstrim
static char	*ft_mallocresu(int lens1, int trimdeb, int trimfin, char *s1)
{
	char	*resu;
	int		i;

	if ((lens1 - trimdeb - trimfin) < 0)
		resu = malloc (sizeof(char));
	else
		resu = malloc ((lens1 - trimdeb - trimfin + 1) * sizeof(char));
	if (!resu)
		return (NULL);
	i = trimdeb;
	while (i < lens1 - trimfin)
	{
		resu[i - trimdeb] = s1[i];
		i++;
	}
	resu[i - trimdeb] = '\0';
	return (resu);
}	

// remove the char contained in set at the beginning aand the end os s1
char	*ft_strtrim(char *s1, char *set)
{
	int		lens1;
	int		trimdeb;
	int		trimfin;
	char	*resu;

	trimdeb = 0;
	trimfin = 0;
	if (!set || !s1)
		return (NULL);
	while (ft_isinlist(s1[trimdeb], set) == 1 && s1[trimdeb] != '\0')
		trimdeb++;
	lens1 = ft_strlen(s1);
	while (ft_isinlist(s1[lens1 - trimfin - 1], set) == 1 && trimfin < lens1)
		trimfin++;
	resu = ft_mallocresu(lens1, trimdeb, trimfin, s1);
	return (resu);
}

// malloc with 0 everywhere inse=ide the vaiable
void	*ft_calloc(size_t count, size_t size)
{
	void	*resu;
	size_t	i;

	resu = malloc(count * size);
	if (!resu)
		return (0);
	i = 0;
	while (i < count * size)
	{
		((unsigned char *)resu)[i] = 0;
		i++;
	}
	return (resu);
}
