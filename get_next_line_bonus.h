/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:27:59 by jurodrig          #+#    #+#             */
/*   Updated: 2024/04/05 04:00:53 by jurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif
# if BUFFER_SIZE > 125000 || BUFFER_SIZE < 1
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif

# ifndef MAX_OPEN_FILES
#  define MAX_OPEN_FILES 512
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

char	*get_next_line(int fd);
char	*read_and_extract_line(char *line, char *stash, int *eol_loc, int fd);
char	*init_stash_line(char *stash, int *eol_loc);
size_t	find_eol_position(char *line);

size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin_gnl(char *s1, char *s2, int *eol_loc);
void	ft_strlcpy_gnl(char *dst, const char *src, size_t dstsize);

#endif