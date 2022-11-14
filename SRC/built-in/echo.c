/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:37:12 by clecat            #+#    #+#             */
/*   Updated: 2022/11/14 16:16:17 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*echo sans arg affiche une ligne vide puis le prompt
echo (num/string) affiche la string
echo -n n'affiche pas la nouvelle ligne
echo -n-n-n-n-n-n affiche le -n-n-n-...
echo -nnnnnnn même comportement que -n
echo -nnnnn5nnnn affiche -nnnnn5nnnn
echo $PATH ou "$PATH" affiche /Users/clecat/.brew/bin:/Users/clecat/... lexer
echo '$PATH' affiche $PATH lexer
echo $ affiche $ sur new line puis prompt sur new line 
echo $? affiche la valeur lexer */
int	echo(char **arg)
{
	int i = 0;
	int j = 0;
	
	printf("dans echo\n");
	printf("%s\n", arg[0]);
	if(arg[1][0] == 45)
		return(1);
	else if(!arg[1])
	{
		printf("\n");
		return (0);
	}
	while((arg[i][j] >= 33 && arg[i][j] <= 126) && arg[i][0] != 45)
	{
		printf("%s\n", arg[i]);
		i++;
	}
	return(0);
}

int	main(void)
{
	char **arg;
	arg = malloc(sizeof(char *) * 4);
	
	arg[0] = "echo";
	/*arg[1] = "-n";
	arg[2] = "bonjour";*/
	arg[1] = NULL;
	printf("main\n");
	echo(arg);
}