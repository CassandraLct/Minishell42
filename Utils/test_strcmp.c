
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	l1;
	int	l2;

	l1 = strlen(s1);
	l2 = strlen(s2);
	if (l1 == l2)
		return (strncmp(s1, s2, l1));
	else
		return (l1 - l2);
}

int main(void)
{
	char	*s1;
	char	*s2;
	int		ret;
	int		ret2;

	s1 = "Hello";
	s2 = "Groupe42";
	ret = ft_strcmp(s1, s2);
	ret2 = strcmp(s1, s2);
	printf("ret = %d, ret2 = %d\n", ret, ret2);
	exit (0);
}