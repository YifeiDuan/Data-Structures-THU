#include<stdio.h>
#include<string.h>
struct node
{
	int a;
	int b;
};
long long int totalCost;
int price;
int effect;
int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	struct node *bridges = new struct node[n];
	struct node *materials = new struct node[m];
	
	int i , j;
	for(i = 0 ; i < n ; i ++) scanf("%d %d\n" , &bridges[i].a , &bridges[i].b);
	for(i = 0 ; i < m ; i ++)
	{
		if(i == m- 1) scanf("%d %d" , &materials[i].a , &materials[i].b);
		else scanf("%d %d\n" , &materials[i].a , &materials[i].b);
	}
	
	totalCost = 0;
	int tag = 0;
	for(i = 0 ; i < n ; i ++)
	{		
	    price = 2000000000;
	    effect = 2000000000;
		for(j = 0 ; j < m ; j ++)
		{
			if((materials[j].a <= price)&&(materials[j].a >= bridges[i].a))
			{
				if((materials[j].b < effect)&&(materials[j].b >= bridges[i].b))
				{
					tag = j;
					price = materials[j].a;
					effect = materials[j].b;
				}
				else tag += 0;
			}
			else continue;
		}
		totalCost += (long long int)price;
		materials[tag].a = 0;
		materials[tag].b = 0;
	}
	
	printf("%lld" , totalCost);
}
