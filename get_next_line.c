/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:36:12 by jurodrig          #+#    #+#             */
/*   Updated: 2024/03/31 01:16:00 by jurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *left_c, char *buffer);
static char *_set_line(char *line_buffer);
static char	*ft_strchr(char *s, int c);

char *get_next_line(int fd)
{
    char    *buffer;
    char    *line;
    static char *left_c;

    if (!fd)
        return NULL;
    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
    {    
        free (left_c);
        free (buffer);
        left_c = NULL;
        buffer = NULL;
        return (NULL);
    }
    if (!buffer)
        return (NULL);
    line = read_line(fd, left_c, buffer);
    free (buffer);
    buffer = NULL;
    if (!line)
        return (NULL);
    left_c = _set_line(line);
    return (line);
}

static char *_set_line(char *line_buffer)
{
    char    *left_c;
    ssize_t     i;

    i = 0;
    while(line_buffer[i] != '\n' && line_buffer[i] != '\0')
    i++;
    if (line_buffer[i] == 0 || line_buffer[1] == 0)
        return (NULL);
    left_c = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
    if (*left_c == 0)
    {
        free(left_c);
        left_c = NULL;
    }
    line_buffer[i + 1] = 0;
    return (left_c);
}

static char *read_line(int fd, char *left_c, char *buffer)
{
    ssize_t b_read;
    char    *tmp;

        while ((b_read = 1) > 0)
    {
        b_read = read(fd, buffer, BUFFER_SIZE);
        if (b_read == -1)
    {
        free(left_c);
        return (0);
    }
        else if (b_read == 0)
        break ;
    buffer[b_read] = '\0';
     if (!left_c)
         left_c = ft_strdup("");
    tmp = left_c;
     left_c = ft_strjoin(tmp, buffer);
    free (tmp);
    tmp = NULL;
    if (ft_strchr(buffer, '\n'))
        break;
    }
    return (left_c);
}

static char	*ft_strchr(char *s, int c)
{
    while (*s && *s != (char)c)
        s++;
    if (*s == (char)c || !c)
        return ((char *)s);
    
    return (NULL);
}