/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:00:18 by abonneau          #+#    #+#             */
/*   Updated: 2024/12/04 19:48:17 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

char    *return_next_line(char *buf, char *line)
{
    char   *next_line;
    if (!line)
        return (ft_strdup(buf));
    next_line = ft_strjoin(line, buf);
    free(line);
    return (next_line);
}

char	*get_next_line(int fd)
{
    static  char    *remaining;
    char	buf[BUFFER_SIZE + 1];
    char	*line;
    int		ret;
    char    *c;
    char    *temp;

    line = NULL;


    if (remaining)
    {
        c = ft_strchr(remaining, '\n');
        if (c)
        {
            *c = '\0';
            line = ft_strdup(remaining);
            temp = ft_strdup(c + 1);
            free(remaining);
            remaining = temp;
            return (line);
        }
        line = ft_strdup(remaining);
        free(remaining);
        remaining = NULL;
    }

    ret = read(fd, buf, BUFFER_SIZE);
    if (ret <= 0)
        return (line);
    buf[ret] = '\0';

    c = ft_strchr(buf, '\n');
    if (c)
    {
        *c = '\0';
        remaining = ft_strdup(c + 1);
        return (return_next_line(buf, line));
    }
    return (return_next_line(buf, line));
}
