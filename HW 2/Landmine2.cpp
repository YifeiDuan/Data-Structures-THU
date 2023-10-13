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
	for(i = 1 ; i <= m - 1 ; i ++) //������������ 
	{
		for(j = 1 ; j <= n - 1 ; j ++)
		{
			scanf("%d " , &temp); //����������0/1���ݼ�¼temp 
			if(temp == 1) //��tempΪ1 
			{
				for(k = tag[j] + 1 ; k <= i ; k ++) histograms[k][j] += 1; //����д�tag��������ÿ��Ԫ�ص��ۼ�ֵ��1 
			}
			else tag[j] = i; //��tempΪ0�������tagλ�� 
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
	
	for(i = 1 ; i <= m ; i ++) countRowi(histograms[i]); //��ÿ�������� 
	printf("%d" , result);
}
void countRowi(int *p)
{
	int width , top , length; //width��length���ڱ�ʾҪ���ҵľ��εĿ���ֵ��topָʾ�������ϽǶ����λ�ã���������ͬ���ڱ�֤���Ҳ��ز�©�� 
	for(top = 1 ; top <= n ; top ++) //��topΪ���ѭ����ѭ��������ȷ��ÿ�ν������ѭ��ʱ�����ҵľ��ζ����в�ͬ�����ϽǶ��� 
	{
		if(p[top] == 0) continue;
		else
		{
			for(width = 1 ; width <= mmax ; width ++) //�в�ѭ��ȷ��ÿ�ν���ʱ�����ҵľ��ξ��в�ͬ��ȣ���mmaxΪ�� 
			{
				if(width <= p[top]) //�����������p[top]��Χ�ڣ�����Խ�һ������ 
				{
					for(length = 1 ; length <= nmax ; length ++) //�ڲ�ѭ��ȷ��ÿ�ν���ʱ�����ҵľ��ξ��в�ͬ���ȣ���nmaxΪ�� 
				    {
					    if(n >= top - 1 + length) //�����topλ�ÿ�ʼ������Ȼ����ܳ���n��Χ�ڣ�����Խ�һ������ 
					    {
					    	if(width <= p[top - 1 + length]) result = (result + 1)%10007; //���widthС������pֵ������������С�ڴ�top������ÿһ��pֵ��������1 
					    	else break; //��������ѭ������ʾ�������µľ��γ��Ȳ����ٵ����ˣ�ȷ��������������������� 
						}
						else break; //���ȵ�һ�δﵽ����Ҫ��ʱ�������ڲ�ѭ�� 
				    }
				}
				else break; //��ȵ�һ�δﵽ����Ҫ��ʱ�������в�ѭ�� 
			}
		}
	}
}
