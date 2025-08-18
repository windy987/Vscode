#include <stdio.h>

int main()  
{
	int m,i = 0,j = 1,k = 0,p,count = 0,point = 0,alive[25];	
	scanf("%d",&m);
	while(1)
	{
		//initialize alive 
		for(p = 0;p <= 2*m;p++)
			alive[p] = 1;
			
		//change and try different k value
		k++;			
		printf("%d\n",k);
		while(1)
		{
			i++;
			
			//return to start
			if(i == m*2 + 1)
				i = 1;
			
			//skip the person who has died
			while(alive[i] == 0)
			{
				i++;
				if(i == m*2 + 1)
					i = 1;
			}
			
			point++;
			
			//whenever achieving k vlaue, kill alive[i] and mark him 0
			if(point == k)		
			{
				alive[i] = 0;
				count++;
				point = 0;		
			}
			
			//when killing m individuals, stop
			if(count == m)	
				break;
		}
		
		//return
		i = 0;
		count = 0;				
		j = 1;
		
		//test whether all good people are alive
		while(j <= m)
		{
			if(alive[j] == 1)	
				j++;
			else 
				break;
		}
		if(j == m + 1)
			break;
	}
	printf("%d",k);
}

	
	
