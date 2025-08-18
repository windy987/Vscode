#include<stdio.h>
#include<string.h>

//字符串反转函数 
void transpose(char a[])
{
	int len = strlen(a);
	for (int i = 0; i < len/2 ; i++)
	{
		char t;
		t = a[i];
		a[i] = a[len - i - 1];
		a[len - i - 1] = t;
	}
}

//找到一个字符串的所有子串并存在C数组中 
void substring(char a[],char c[][200])
{
	int i,j,k,l = 0; 
	int len = strlen(a);
	
	//i代表最顶层字串长度
	for (i = 1; i <= len ; i++)
	{
		//j代表第二层字串开始处原字符串下标 
		for (j = 0; j + i <= len ; j++)
		{
			//k代表存储数组c的二维索引,l代表一维索引(也就是第几个) 
			for (k = 0; k < i ; k++) 
			{
				c[l][k] = a[j + k];
			}
			c[l][k] = '\0'; //添加结尾符
			l++;
			//加入反转子串 
			strcpy(c[l],c[l-1]);
			transpose(c[l]);
			l++;
		}
	}
}
















