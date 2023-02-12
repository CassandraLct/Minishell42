/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errmsg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdi-marz <rdi-marz@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:59:04 by rdi-marz          #+#    #+#             */
/*   Updated: 2023/02/12 15:41:13 by rdi-marz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print error message on fd = 2 with 3 char *
void	ft_print_error_msg3(char *s1, char *s2, char *s3)
{
	write(2, s1, ft_strlen(s1));
	write(2, s2, ft_strlen(s2));
	write(2, s3, ft_strlen(s3));
}

// print error message on fd = 2 for export
void	ft_export_error_msg(char *s1, char *s2)
{
	write(2, "minishell: ", 11);
	write(2, s1, ft_strlen(s1));
	write(2, ": `", 3);
	write(2, s2, ft_strlen(s2));
	write(2, "': not a valid identifier\n", 26);
}
