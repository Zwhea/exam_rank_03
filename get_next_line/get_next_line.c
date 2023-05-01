/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wangthea <wangthea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 13:49:25 by wangthea          #+#    #+#             */
/*   Updated: 2023/05/01 13:49:26 by wangthea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(char *s)
{
	if (!s)
		return (0);
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int ft_strchr(char *s, char c)
{
	if (!s || !c)
		return (0);
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

static char	*ft_calloc(int count, int size)
{
	char	*str;
	int	i;

	i = 0;
	if (count < 0)
		return (NULL);
	str = (char *)malloc(count * size);
	while (i < count)
		str[i++] = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str_join;
	int	i = 0;
	int	j = 0;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (s1);
	str_join = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	while (s1[i])
	{
		str_join[i] = s1[i];
		i++;
	}
	while (s2[j])
		str_join[i++] = s2[j++];
	free(s1);
	return (str_join);
}
static char	*get_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
		return (free(stash), NULL);
	new_stash = ft_calloc((ft_strlen(stash) - i) + 1, sizeof(char));
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	free(stash);
	return (new_stash);
}

static char	*get_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (!stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line = NULL;
	char		buffer[BUFFER_SIZE + 1];
	int			i = 1;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (i > 0 && ft_strchr(stash, '\n') == 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
			return (free(stash), NULL);
		buffer[i] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	line = get_line(stash);
	stash = get_stash(stash);
	return (line);
}

#include <stdio.h>
#include <fcntl.h>

int main(int ac, char **av)
{
	(void)ac;
	char *line = NULL;
	int fd = open(av[1], O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	return (0);
}
