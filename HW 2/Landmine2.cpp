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
	for(i = 1 ; i <= m - 1 ; i ++) //遍历土地网格 
	{
		for(j = 1 ; j <= n - 1 ; j ++)
		{
			scanf("%d " , &temp); //对土地网格0/1数据记录temp 
			if(temp == 1) //若temp为1 
			{
				for(k = tag[j] + 1 ; k <= i ; k ++) histograms[k][j] += 1; //则该列从tag处至该行每个元素的累计值加1 
			}
			else tag[j] = i; //若temp为0，则更新tag位置 
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
	
	for(i = 1 ; i <= m ; i ++) countRowi(histograms[i]); //对每行做计数 
	printf("%d" , result);
}
void countRowi(int *p)
{
	int width , top , length; //width、length用于表示要查找的矩形的宽、长值，top指示矩形左上角顶点的位置（三个量共同用于保证查找不重不漏） 
	for(top = 1 ; top <= n ; top ++) //以top为外层循环的循环变量，确保每次进入外层循环时所查找的矩形都具有不同的左上角顶点 
	{
		if(p[top] == 0) continue;
		else
		{
			for(width = 1 ; width <= mmax ; width ++) //中层循环确保每次进入时所查找的矩形具有不同宽度，以mmax为界 
			{
				if(width <= p[top]) //如果这个宽度在p[top]范围内，则可以进一步查找 
				{
					for(length = 1 ; length <= nmax ; length ++) //内层循环确保每次进入时所查找的矩形具有不同长度，以nmax为界 
				    {
					    if(n >= top - 1 + length) //如果从top位置开始这个长度还在总长度n范围内，则可以进一步查找 
					    {
					    	if(width <= p[top - 1 + length]) result = (result + 1)%10007; //如果width小于这点的p值（隐含条件：小于从top至这点的每一个p值）则结果加1 
					    	else break; //否则跳出循环，表示这个宽度下的矩形长度不能再递增了，确保了上面的隐含条件成立 
						}
						else break; //长度第一次达到不合要求时则跳出内层循环 
				    }
				}
				else break; //宽度第一次达到不合要求时则跳出中层循环 
			}
		}
	}
}
