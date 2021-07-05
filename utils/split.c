#include "../pipex.h"

static int	ft_word_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_word_count(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] == c && s[j])
			j++;
		if (!s[j])
			break ;
		i++;
		while (s[j] != c && s[j])
			j++;
	}
	return (i);
}

static char	**ft_fill(char **str, char *s, char ch, int len)
{
	int	i;
	int	g;

	i = 0;
	while (i < len)
	{
		while (*s == ch && *s)
			s++;
		g = ft_word_len(s, ch);
		str[i] = ft_substr(s, 0, g);
		if (!str[i])
			exit(1);
		while (*s != ch && *s)
			s++;
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char *s, char c)
{
	int		len;
	char	**res;

	if (!s)
		return (NULL);
	len = ft_word_count(s, c);
	res = (char **)malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	res = ft_fill(res, s, c, len);
	return (res);
}
