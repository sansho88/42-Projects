/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GET_NEXT_LINE.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:25:37 by tgriffit          #+#    #+#             */
/*   Updated: 2021/12/06 11:28:00 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_vars {
	int				bytes;
	char			buffer[BUFFER_SIZE + 1];
	char			*rmndr;
}	t_vars;

size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char *s2);
void			*ft_memcpy(void *dst, const void *src, size_t n);
char			*ft_strdup(const char *s1);
char			*get_next_line(int fd);
char			*ft_strnstr(const char *haystack, const char *needle, size_t n);
#endif
