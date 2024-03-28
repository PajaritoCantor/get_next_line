/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:36:12 by jurodrig          #+#    #+#             */
/*   Updated: 2024/03/27 22:21:21 by jurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*_fill_line_buffer(int fd, char *left_c, char *buffer);
static char *_set_line(char *line_buffer);
static char *ft_strchr(char *s, int c);

char	*get_next_line(int fd)
{
	char	*buffer;
	static char	*left_c;
	char	*line;
	
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) - 0)
	{
		free(left_c);
		free(buffer);
		left_c = NULL;
		buffer = NULL;
		return (NULL);
	if(!buffer)
		return (NULL);
	line = _fill_line_buffer(fd, left_c, buffer);
	free(buffer);
	buffer = NULL;
	if(!line)
		return (NULL);
	}
}	

static char *_fill_line_buffer(int fd, char *left_c, char *buffer)
{
	ssize_t b_read;
	char *tmp;

	b_read = read(fd, buffer, BUFFER_SIZE);

    while (b_read > 0)
    {
        if (b_read == -1)
        {
            free(left_c);
            return (NULL);
        }
        else if (b_read == 0)
        {
            break;
        }
        buffer[b_read] = '\0';
        if (ft_strchr(buffer, '\n'))
        {
            break;
        }
        b_read = read(fd, buffer, BUFFER_SIZE);
    }
    if (b_read == -1)
    {
        free(left_c);
        return (NULL);
    }
    if (!left_c)
        left_c = ft_strdup("");
    tmp = left_c;
    left_c = ft_strjoin(tmp, buffer);
    free(tmp);
    tmp = NULL;
    return left_c;
}

	