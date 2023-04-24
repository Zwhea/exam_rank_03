/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:35:40 by wangthea          #+#    #+#             */
/*   Updated: 2023/04/24 18:35:41 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    if (BUFFER_SIZE <= 0)
        return (NULL);
		
    int     i = 0;
    int     rd = 0;
    char    character;
    char    *buffer = malloc(100000);

	while ((rd = read(fd, &character, BUFFER_SIZE - BUFFER_SIZE + 1)) > 0)
    {
        buffer[i++] = character;
        if (character == '\n')
            break ;
    }
    buffer[i] =  '\0';
    if (rd == -1 || i == 0 || (!buffer[i - 1] && !rd))
        return (free(buffer), NULL);
    return(buffer);
}

/*---- test main ----
#include <fcntl.h>
#include <stdio.h>

#define BUFFER_SIZE 10

int main(int ac, char **av)
{
	(void)ac;
    int fd;
    char *line;

    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        puts("open error");

    while ((line = get_next_line(fd)))
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return (0);
}
*/