#include "../pipex.h"

int32_t	ft_strncmp(const char *s1, const char *s2, int32_t n)
{
	int32_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && i < n && (str1[i] || str2[i]))
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (i != n)
		return (str1[i] - str2[i]);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, int32_t len)
{
	char	*substr;
	int		j;
	int		i;

	if (!s)
		return (NULL);
	j = start;
	i = 0;
	if (start >= strlen(s))
		return (strdup(""));
	substr = (char *)malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (len > 0 && s[j])
	{
		substr[i] = s[j];
		j++;
		i++;
		len--;
	}
	substr[i] = '\0';
	return (substr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	char	*tmp;
	int		i;

	i = 0;
	new = calloc(sizeof(char), (strlen(s1) + strlen(s2) + 1));
	if (!new)
		return (NULL);
	tmp = new;
	while (s1 && s1[i])
	{
		*new = s1[i];
		new++;
		i++;
	}
	if (s1)
		free(s1);
	while (s2 && *s2)
	{
		*new = *s2;
		new++;
		s2++;
	}
	return (tmp);
}
