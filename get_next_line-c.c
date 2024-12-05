/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line-c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:00:18 by abonneau          #+#    #+#             */
/*   Updated: 2024/12/05 00:56:43 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

static char    *return_next_line(char *buf, char *line)
{
    char   *next_line;
    char   *temp;
    
    if (!line)
    {
        temp = ft_strdup(buf);
        free(buf);
        return (temp);
    }
    next_line = ft_strjoin(line, buf);
    free(line);
    free(buf);
    return (next_line);
}

static char *method(char **remaining, char **line)
{
    char    *c;
    char    *temp;
    
    if (*remaining)
    {
        c = has_line_break(*remaining);
        if (c)
        {
            *c = '\0';
            *line = ft_strdup(*remaining);
            temp = ft_strdup(c + 1);
            free(*remaining);
            *remaining = temp;
            //if (!temp)
            //    return (-1);
            //return (*line);
        }
        *line = ft_strdup(*remaining);
        free(*remaining);
        *remaining = NULL;
    }
}

char	*get_next_line(int fd)
{
    static  char    *remaining;
    char	buf[BUFFER_SIZE + 1];
    char    *buf2; 
    char	*line;
    int		ret;
    char    *c;
    char    *temp;

    line = NULL;
    buf2 = NULL;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    method(&remaining, &line);
    if (remaining)
        return (line);
    while (1)
    {
        ret = read(fd, buf, BUFFER_SIZE);
        if (ret <= 0)
            return (return_next_line(buf2, line));
        buf[ret] = '\0';
        if (!buf2)
            buf2 = ft_strdup(buf);
        if (!buf2)
            return (NULL);
        temp = ft_strjoin(buf2, buf);
        free(buf2);
        buf2 = temp;


        c = has_line_break(buf2);
        if (c)
        {
            *c = '\0';
            remaining = ft_strdup(c + 1);
            return (return_next_line(buf2, line));
        }
    }
}
