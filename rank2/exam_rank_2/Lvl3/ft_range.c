#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int *ft_range (int start, int end)
{
	int  *ls;
	int len = 1;
	int aux = start;
	int i =0;
	if (start < end)
	{
		while (aux <= end)
		{
			len++;
			aux++;
		}
		ls = malloc(sizeof(int)*(len + 1));
		if (!ls)
			return NULL;
		while(start <= end)
		{
			ls[i] = start;
			i++;
			start++;
		}
	}
	else
	{
		while (aux >= end)
                {
                        len++;
                        aux--;
                }
                ls = malloc(sizeof(int)*(len + 1));
                if (!ls)
                        return NULL;
                while(start >= end)
                {
                        ls[i] = start;
                        i++;
                        start--;
                }
	}	
		return ls;

}
/*
int main ()
{
	int i =0;
	int *nums;

	nums = ft_range(-1,-3);
	while ( nums[i] || nums[i + 1])
	{
		printf("%i",nums[i]);
		i++;
	}
	return 0;

}*/
