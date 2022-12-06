/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:33:18 by clecat            #+#    #+#             */
/*   Updated: 2022/12/06 11:12:06 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* signaux: ctrl-c / ctrl-d / ctrl-\
droit a la fonction signal

quand prog en train de compiler
ctrl-D kill le term
ctrl-C stop le prog et affiche err
ctrl-\ stop le prog

ctrl-c dans heredoc quitte heredoc
ctrl-d dans heredoc affiche erreur grep puis quitte
ctrl-\ dans heredoc ne fait rien*/
