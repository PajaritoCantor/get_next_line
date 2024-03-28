/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurodrig <jurodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 07:49:45 by jurodrig          #+#    #+#             */
/*   Updated: 2024/03/27 17:04:45 by jurodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
    int		fd;
    char	*line;

    fd = open("test.txt", O_RDONLY, 777);
    if (fd == -1)
    {
        printf("Error\n");
        return (1);
    }
    while ((line = get_next_line(0)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }	
    /*if (close(fd) == -1)
    {
        printf("error al cerrar\n");
        return (1);
    }*/
    return (0);
}