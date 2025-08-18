#include<stdio.h>
#include<string.h>

//calculate power of 2
int fun(int n)   
{
	int mul;
	if(n == 0)
		mul = 1;
	if(n == 1)
		mul = 2;
	if(n == 2)
		mul = 4;
	if(n == 3)
		mul = 8;
	return mul;
}

int main()
{
	char s[500000],a[500000];
	scanf("%s",s);
	int front = 0,len = strlen(s),i = 0;
	
	//test the full zero input
    int allZero = 1;
    for (int x = 0; x < len; x++)
	 {
        if (s[x] == '1') 
		{
            allZero = 0;
            break;
        }
    }
    
    // if full zero, stop
    if (allZero) 
	{
        printf("0\n");
        return 0;
    }
	
	//add 0 to the front
	int add = 0;
	add = 4 - (len % 4);
		
	//calcualte the front 4 number and store the result in front
	int step = 4-add;
	while(step--)
		front += fun(step) * (s[i++] - '0');

	//everytime when calculated 4 numbers, change to the next group and store the result in a
	int count = 0;
	int group = 4;
	int sum = 0;
	
	while(i < len)
	{
		while(group--)
			sum += fun(group) * (s[i++] - '0');
		a[count++] = sum;
		group = 4;
		sum = 0;
	}
		
	//convert
	for(int j = 0;j < len / 4 ;j++)		
	{
		switch(a[j])
		{
		case 10 :
			a[j] = 'A';
			break;
		case 11 :
			a[j] = 'B';
			break;
		case 12 :
			a[j] = 'C';
			break;
		case 13 :
			a[j] = 'D';
			break;
		case 14 :
			a[j] = 'E';
			break;
		case 15 :
			a[j] = 'F';
			break;
		default :
			a[j] += '0';
		}
	}
	
	//if front != 0, print as the first
	if(front != 0)
		printf("%d",front);
	
	//print the left		
	for(int j = 0;j < len / 4;j++)
		printf("%c",a[j]);
}
	
	
