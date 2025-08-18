#include<stdio.h>
#include<string.h>

int main()
{
	char a[100][25];
	int i,j,n;
	scanf("%d", &n);
	for (i = 0; i < n ; i++)
		scanf("%s", a[i]);
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - 1 - i ; j++)
		{
			char ab[50], ba[50];
			strcpy(ab, a[j]);
			strcat(ab, a[j+1]);
			strcpy(ba, a[j+1]);
			strcat(ba, a[j]);
			if (strcmp(ab, ba) < 0) 
			{
			    char t[25];
			    strcpy(t, a[j]);
			    strcpy(a[j], a[j+1]);
			    strcpy(a[j+1], t);
			}
		}
	}
	char final[3000];
	strcpy(final, a[0]);
	for (i = 1; i < n ; i++)
	{
		strcat(final, a[i]);
	}
	printf("%s",final);
}











