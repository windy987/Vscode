#include<stdio.h>

int main()
{
	int l;  	 //length
	int m;	     //numbers of ranges
	int a,b;	 //boths ends of the ranges
	int sum = 0; //calculate the original array 
	int count = 0;//count the tree cut down
	int i;		 //loop viriable
	
	//main input
	scanf("%d",&l);
	scanf("%d",&m);
	
	int s[l+1];  //the origin array
	int d[l+1];	 //the difference array
	
	//assign values to the arrays
	s[0] = 1;
	d[0] = 1;
	for(i = 1;i <= l; i++)
	{
		s[i] = 1;
		d[i] = s[i] - s[i-1];
	}
	
	//process each range in turn
	while(m--)
	{
		scanf("%d",&a);  //left end of a range
		scanf("%d",&b);  //right end of a range
		
		//change the difference array 
		if(b == l)		//when b reaches the right end, not change
			d[a]--;
		else
		{
			d[a]--;		//left minus
			d[b+1]++;	//right add
		}
	}
	
	//calculate the original array 
	for(i = 0;i <= l; i++)
	{
		sum += d[i];
		if(sum < 1)
			count ++;	
	}
	printf("%d",l + 1 - count);
}
