#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int ft_strlen(char *src)
{
	int i = 0;
	while (src[i] && src[i] != '\0')
		i++;
	return i;
}
char	*ft_strdup(char *src)
{
	int i = 0;
	char *dst;	

	dst = malloc(sizeof(char)*(ft_strlen(src) + 1));
	if(dst)
	{
		while(src[i] && src[i] !='\0')
	
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return dst;
		
}

/*int main()
{
	char *s = "hola q tal";
	char *c;
	c = ft_strdup(s);
	printf("%s", c);
}*/
