#include<stdio.h>
#include<string.h>

int n , m , nmax , mmax; //ǰ���������� 
int result; //������� 
int histograms[2001][2001]; //�ö�ά��������ÿһ��ά��һ�����ε����У�ÿ�����δ�СΪ���и���Ԫ����������Ϊ1�ĳ��� 
void countRowi(int *p); //���ڼ����ĺ���������Ϊhistograms�е�һ�� 
int main()
{
	scanf("%d %d\n" , &n , &m);
	scanf("%d %d\n" , &nmax , &mmax);
	result = 0;
	
	int i , j , k , temp;
	int *tag = new int[n + 1]; //���ڱ��ÿһ�������µ�һ��0�㣬��Ϊ����������0/1�����λ�ö�histograms��Ԫ�ص�ȡֵ������Ҫ 
	for(i = 0 ; i <= n ; i ++) tag[i] = 0; 
	for(i = 0 ; i <= 2000 ; i ++)
	{
		for(j = 0 ; j <= 2000 ; j ++) histograms[i][j] = 0; //��histograms��ֵ����0 
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

