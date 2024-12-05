#include <get_next_line.h>


char *handle_line(char **remaining)
{
	char *line;
	
}

char *get_next_line(int fd)
{
	static char *remaining;
	char buffer[BUFFER_SIZE + 1];
	char *tmp;
	int read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remaining)
		remaining = ft_strdup("");
	if (!remaining)
		return (NULL);
	while (!ft_strchr(remaining, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
		    break;
		buffer[read_bytes] = '\0';
		tmp = ft_strjoin(remaining, buffer);
		free(remaining);
		if (!remaining)
			return (NULL);
		remaining = tmp;
	}
	return (handle_line(&remaining));
}