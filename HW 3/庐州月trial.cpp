#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct lz //记录桥/石材的结构体 
{
	int x;
	int y;
};

long long int totalCost;

int cmpfunc (const void * a, const void * b);

int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	
	struct lz *bridge = new struct lz[n];
	struct lz *material = new struct lz[m];
	
	int i , j , k;
	for(i = 0 ; i < n ; i ++) scanf("%d %d\n" , &bridge[i].x , &bridge[i].y);
	for(i = 0 ; i < m ; i ++)
	{
		if(i == m - 1) scanf("%d %d" , &material[i].x , &material[i].y);
		else  scanf("%d %d\n" , &material[i].x , &material[i].y);
	}
	
	qsort(bridge , n , sizeof(bridge[0]) , cmpfunc);
	qsort(material , m , sizeof(material[0]) , cmpfunc);
	
	/*for(i = 0 ; i < n ; i ++) printf("%d " , bridge[i].y);
	printf("\n");
	for(i = 0 ; i < m ; i ++) printf("%d " , material[i].y);
	*/
	totalCost = 0;
	/*int tag = 0;
	for(i = 0 ; i < n ; i ++ )
	{
		for(j = tag ; j < m ; j ++)
		{
			if(bridge[i].x <= material[j].x)
			{
				for(k = j ; k < m ; k ++)
				{
					if(bridge[i].y <= material[k].y)
					{
						totalCost += (long long int) material[k].x;
						material[k].x = 0;
						goto finish;
					}
					else continue;
				}
			}
			else continue;
		}
	finish:
		tag = j;
	}*/
	printf("%lld" , totalCost);
}

int cmpfunc (const void * a, const void * b)
{
   return (*(lz *)a).y > (*(lz *)b).y ? 1 : -1;
}
