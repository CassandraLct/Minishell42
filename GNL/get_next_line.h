/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clecat <clecat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:22:34 by clecat            #+#    #+#             */
/*   Updated: 2023/02/03 13:08:43 by clecat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>

# define BUFFER_SIZE 1

char	*get_next_line(int fd);
size_t	ft_strlen2(const char *str);
char	*ft_strjoin2(char *str, char *buf);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc3(size_t count, size_t size);

#endif
