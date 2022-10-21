/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:38:06 by clecat            #+#    #+#             */
/*   Updated: 2022/10/21 13:11:30 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Minishell.h"

//valgrind --leak-check ./minishell

int main(int argc, char **argv, char **env)
{
	char *line;
	
	while(1)
	{
		line = readline("minishell>");
	}
}