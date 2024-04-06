/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:45:35 by jurodrig          #+#    #+#             */
/*   Updated: 2024/04/05 01:14:17 by jurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*init_stash_line(char *buffer_tmp, int *eol_loc)
{
	size_t	len;
	char	*line_text;

	len = 0;
	while (buffer_tmp[len] && buffer_tmp[len] != '\n')
		len++;
	len++;
	line_text = malloc(sizeof(char) * (len + 1));
	if (!line_text)
		return (NULL);
	ft_memcpy(line_text, buffer_tmp, len);
	line_text[len] = '\0';
	if (len > 0 && line_text[len - 1] == '\n')
		*eol_loc = len - 1;
	return (line_text);
}

size_t	find_eol_position(char *line_text)
{
	size_t	i;

	i = 0;
	if (!line_text)
		return (-1);
	while (i < BUFFER_SIZE)
	{
		if (line_text[i] == '\n' || line_text[i] == '\0')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*read_and_extract_line(char *line_text, char *buffer_tmp, int *eol_loc,
int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	size_t	line_length;

	while (*eol_loc == -1)
	{
		ft_bzero(buffer, (BUFFER_SIZE + 1));
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(line_text);
			ft_bzero(buffer_tmp, (BUFFER_SIZE + 1));
			return (NULL);
		}
		line_length = find_eol_position(buffer);
		ft_strlcpy_gnl(buffer_tmp, &buffer[line_length], (BUFFER_SIZE + 1));
		buffer[line_length] = '\0';
		line_text = ft_strjoin_gnl(line_text, buffer, eol_loc);
		if (bytes_read == 0)
		{
			ft_bzero(buffer_tmp, BUFFER_SIZE + 1);
			break ;
		}
	}
	return (line_text);
}

char	*get_next_line(int fd)
{
	static char	buffer_tmp[OPEN_MAX][BUFFER_SIZE + 1];
	char		*line_text;
	int			eol_loc;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	eol_loc = -1;
	line_text = init_stash_line(buffer_tmp[fd], &eol_loc);
	if (!line_text)
		return (NULL);
	ft_strlcpy_gnl(buffer_tmp[fd], &buffer_tmp[fd][eol_loc + 1],
		BUFFER_SIZE + 1);
	line_text = read_and_extract_line(line_text, buffer_tmp[fd], &eol_loc, fd);
	if (!line_text || line_text[0] == '\0')
	{
		free(line_text);
		return (NULL);
	}
	return (line_text);
}

/*
#include <fcntl.h>

int main(void)
{
    int fd1, fd2;
    char *line;

    fd1 = open("test.txt", O_RDONLY);
    fd2 = open("ejemplo.txt", O_RDONLY);
    if (fd1 == -1 || fd2 == -1)
    {
        printf("Error al abrir los archivos\n");
        return (1);
    }

    printf("Leyendo test.txt:\n");
    while ((line = get_next_line(fd1)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }

    printf("Leyendo test2.txt:\n");
    while ((line = get_next_line(fd2)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }

    close(fd1);
    close(fd2);
    return (0);
}
*/