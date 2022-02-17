/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:19:32 by tgriffit          #+#    #+#             */
/*   Updated: 2022/01/04 17:37:55 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_chrjoinfree(char *s1, char c, bool mode);
char	*ft_itoa(int n);
void	ft_putstr_fd(char *s, int fd, _Bool mode);
int		ft_atoi(const char *str);
void	ft_putchar(char c);
void	ft_putendl_fd(char *s, int fd);

#endif
