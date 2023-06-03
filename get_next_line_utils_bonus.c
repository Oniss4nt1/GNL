#include "get_next_line.h"
#include <strings.h>

size_t	ft_strlen(char *s)
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

char	*ft_strdup(const char *s)
{
	char	*str;
	char	*p;
	int		len;

	len = 0;
	while (s[len] != '\0')
		len++;
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	p = str;
	while (*s != '\0')
		*p++ = *s++;
	*p = '\0';
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*p;
	char	*original_s1;
	size_t	len_string;

	if (s1 == NULL)
		s1 = ft_strdup("");
	len_string = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(len_string);
	if (str == NULL)
		return (NULL);
	p = str;
	original_s1 = s1;
	while (*s1)
		*p++ = *s1++;
	while (*s2)
		*p++ = *s2++;
	*p = '\0';
	free(original_s1);
	return (str);
}
