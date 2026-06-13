#include "get_next_line.h"

static char	*read_until_newline(int fd, char *stash);
static char	*extract_line(char *stash);
static char	*trim_stash(char *stash);

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = gnl_strdup("");
	stash = read_until_newline(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = trim_stash(stash);
	return (line);
}

static char	*read_until_newline(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !gnl_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(buffer), free(stash), NULL);
		buffer[bytes_read] = '\0';
		stash = gnl_strjoin(stash, buffer);
	}
	free(buffer);
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*newline_pos;
	size_t	line_len;

	if (!stash || stash[0] == '\0')
		return (NULL);
	newline_pos = gnl_strchr(stash, '\n');
	if (newline_pos)
		line_len = (newline_pos - stash) + 1;
	else
		line_len = gnl_strlen(stash);
	return (gnl_substr(stash, 0, line_len));
}

static char	*trim_stash(char *stash)
{
	char	*newline_pos;
	char	*remainder;
	size_t	start;

	newline_pos = gnl_strchr(stash, '\n');
	if (!newline_pos)
	{
		free(stash);
		return (NULL);
	}
	start = (newline_pos - stash) + 1;
	remainder = gnl_substr(stash, start, gnl_strlen(stash) - start);
	free(stash);
	return (remainder);
}
