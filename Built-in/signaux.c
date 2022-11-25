/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:33:18 by clecat            #+#    #+#             */
/*   Updated: 2022/11/25 16:44:01 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* signaux: ctrl-c / ctrl-d / ctrl-\ 
droit a la fonction signal

ctrl-c dans heredoc quitte heredoc
ctrl-d dans heredoc affiche erreur grep puis quitte
ctrl-\ dans heredoc ne fait rien*/
