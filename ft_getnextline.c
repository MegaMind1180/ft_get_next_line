#include "get_next_line.h"
#include_next "libft.h"

char	*get_next_line(int fd)
{
	char		*buf;
	char		*result;
	static char	*leftover;
	size_t		i;
	size_t		n;

	i = 0;
	while (n = read(fd, buf, 41), 1) > 0)
	{
		buf[n] = '\0';
		leftover = strchr(buf, '\n');
		if (leftover)
		{
			i = ft_strlen(buf) - ft_strlen(leftover);
			result = ft_substr(buf, 0, i);
			return (result);
		}
		else
		{
			i = ft_strlen(buf)
			result = ft_strjoin(result, buf)
			
		}
	}
}
