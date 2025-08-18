#include<stdio.h>
#include<string.h>

void transpose(char a[], int len)
{
	int i;
	for (i = 0; i < len/2 ; i++ )
	{
		int temp = a[i];
		a[i] = a[len - i - 1];
		a[len - i - 1] = temp;
	}
}

void subtraction(char a[], char b[], char c[])
{
	int i;
	int carry = 0;
	int lena = strlen(a);
	int lenb = strlen(b);
	transpose(a,lena);
	transpose(b,lenb);
	for (i = 0; i < lena ; i++ )
	{
		int x = a[i] - '0';                  
		int y = (i < lenb) ? (b[i] - '0') : 0; 
		x -= carry;
		if (x >= y)
		{
			c[i] = (x - y) + '0';
			carry = 0;
		}
		else
		{
			c[i] = (x + 10 - y) + '0';
			carry = 1;
		}
	}
	c[i] = '\0';
	transpose(c,strlen(c));
}

int main()
{
	int i;
	char a[300],b[300],c[300];
	scanf("%s %s",a,b);
	subtraction(a,b,c);
	while (c[i] == '0' && c[i+1] != '\0')
	{
		i++;
	}
	printf("%s\n",c+i);
}

