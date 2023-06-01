#include "get_next_line.h"

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


char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	char	*p;

	if (s1 == NULL)
		s1 = "";
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	p = str;
	while (*s1)
		*p++ = *s1++;
	while (*s2)
		*p++ = *s2++;
	*p = '\0';
	return (str);
}
