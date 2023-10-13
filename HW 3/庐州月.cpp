#include<stdio.h>
#include<string.h>
struct lz //记录桥/石材的结构体 
{
	int x;
	int y;
};
struct lz bridge[500000];
struct lz material[500000];
long long int totalCost;
void mergeSortB(int lo , int hi);
void mergeB(int lo , int mi , int hi);
void mergeSortM(int lo , int hi);
void mergeM(int lo , int mi , int hi);
int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	
	int i , j , k;
	for(i = 0 ; i < n ; i ++) scanf("%d %d\n" , &bridge[i].x , &bridge[i].y);
	for(i = 0 ; i < m ; i ++)
	{
		if(i == m - 1) scanf("%d %d" , &material[i].x , &material[i].y);
		else  scanf("%d %d\n" , &material[i].x , &material[i].y);
	}
	
	mergeSortB(0 , n);
	mergeSortM(0 , m);
	
	totalCost = 0;
	int tag = 0;
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
	}
	printf("%lld" , totalCost);
}

void mergeSortB(int lo , int hi)
{
	if(hi - lo < 2) return;
	int mi = (lo + hi) >> 1;
	mergeSortB(lo , mi);
	mergeSortB(mi , hi);
	mergeB(lo , mi , hi);
}
void mergeB(int lo , int mi , int hi)
{
	int i , j , k;
	int lb = mi - lo;
	struct lz *B = new struct lz[lb];
	for(i = 0 ; i < lb ; i ++) B[i] = bridge[lo + i];
	int lc = hi = mi;
	for(i = lo , j = 0 , k = mi ; (j < lb) || (k - mi < lc) ; )
	{
		if((j < lb) && ((lc <= k - mi)||(B[j].y < bridge[k].y)||((B[j].y == bridge[k].y)&&(B[j].x < bridge[k].x)))) bridge[i ++] = B[j ++];
		if((k - mi < lc) && ((lb <= j)||(B[j].y > bridge[k].y)||((B[j].y == bridge[k].y)&&(B[j].x > bridge[k].x)))) bridge[i ++] = bridge[k ++];
	}
	delete[] B;
}

void mergeSortM(int lo , int hi)
{
	if(hi - lo < 2) return;
	int mi = (lo + hi) >> 1;
	mergeSortM(lo , mi);
	mergeSortM(mi , hi);
	mergeM(lo , mi , hi);
}
void mergeM(int lo , int mi , int hi)
{
	int i , j , k;
	int lb = mi - lo;
	struct lz *B = new struct lz[lb];
	for(i = 0 ; i < lb ; i ++) B[i] = material[lo + i];
	int lc = hi = mi;
	for(i = lo , j = 0 , k = mi ; (j < lb) || (k - mi < lc) ; )
	{
		if((j < lb) && ((lc <= k - mi)||(B[j].y < material[k].y)||((B[j].y == material[k].y)&&(B[j].x < material[k].x)))) material[i ++] = B[j ++];
		if((k - mi < lc) && ((lb <= j)||(B[j].y > material[k].y)||((B[j].y == material[k].y)&&(B[j].x > material[k].x)))) material[i ++] = material[k ++];
	}
	delete[] B;
}
