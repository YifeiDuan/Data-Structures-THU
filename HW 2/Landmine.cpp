#include<stdio.h>
#include<string.h>

int n , m , nmax , mmax; //前两行输入量 
int result; //结果总数 
int histograms[2001][2001]; //用二维数组来对每一行维护一个矩形的序列，每个矩形大小为该行该列元素向下连续为1的长度 
void countRowi(int *p); //用于计数的函数，参量为histograms中的一行 
int main()
{
	scanf("%d %d\n" , &n , &m);
	scanf("%d %d\n" , &nmax , &mmax);
	result = 0;
	
	int i , j , k , temp;
	int *tag = new int[n + 1]; //用于标记每一列中最新的一个0点，因为土地网格中0/1交界的位置对histograms各元素的取值至关重要 
	for(i = 0 ; i <= n ; i ++) tag[i] = 0; 
	for(i = 0 ; i <= 2000 ; i ++)
	{
		for(j = 0 ; j <= 2000 ; j ++) histograms[i][j] = 0; //将histograms初值均赋0 
	}
	for(i = 1 ; i <= m - 1 ; i ++)
	{
		for(j = 1 ; j <= n - 1 ; j ++)
		{
			scanf("%d " , &temp);
			if(temp == 1)
			{
				for(k = tag[j] + 1 ; k <= i ; k ++) histograms[k][j] += 1;
			}
			else tag[j] = i;
		}
		scanf("%d\n" , &temp);
		if(temp == 1)
		{
			for(k = tag[j] + 1 ; k <= i ; k ++) histograms[k][j] += 1;
		}
		else tag[j] = i;
	}
	for(j = 1 ; j <= n ; j ++)
	{
		scanf("%d" , &temp);
		if(temp == 1)
		{
			for(k = tag[j] + 1 ; k <= i ; k ++) histograms[k][j] += 1;
		}
		else tag[j] = i;
	} 
	
	for(i = 1 ; i <= m ; i ++) 
	{
		for(top = 1 ; top <= n ; top ++)
	    {
		    if(histograms[i][top] == 0) continue;
		    else
		    {
			    for(width = 1 ; width <= mmax ; width ++)
			    {
				    if(width <= histograms[i][top])
				    {
					    for(length = 1 ; length <= nmax ; length ++)
				        {
					        if(n >= top - 1 + length)
						    {
							    if(width <= p[top - 1 + length]) result = (result + 1)%10007;
						    } 
					        else break;
				        }
				    }
				    else break;
			    }
		    }
	    }
	} 
	printf("%d" , result);
}

