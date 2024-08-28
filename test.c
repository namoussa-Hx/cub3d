
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = s;
	while (n)
	{
		*ptr = '\0';
		ptr++;
		n--;
	}
}
void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	result = malloc(count * size);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}

char	*my_strdup(const char *s1, int lenght)
{
	char	*ptr;
	int		i;

	i = 0;
    ptr = (char *)ft_calloc(lenght + 1, sizeof(char));
    if (ptr == NULL)
            return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
int main ()
{
    char *str = "Hello";
    char *str2 = my_strdup(str, 15);
    printf("%s\n", str2);
    return (0);

}
