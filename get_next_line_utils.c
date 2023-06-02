#include "get_next_line.h"
#include <strings.h>

size_t	ft_strlen(const char *s)
{
	size_t	lenght;

	if (s == NULL)
		return (0);
	lenght = 0;
	while (*s != '\0')
	{
		lenght++;
		s++;
	}
	return (lenght);
}


char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*p;
	size_t	len_string;

	if (s1 == NULL)
		s1 = "";
	len_string = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(len_string);
	if (str == NULL)
	{
		free(s1);
		return (NULL);
	}
	p = str;
	while (*s1)
		*p++ = *s1++;
	while (*s2)
		*p++ = *s2++;
	*p = '\0';
	// free(s1);
	return (str);
}
