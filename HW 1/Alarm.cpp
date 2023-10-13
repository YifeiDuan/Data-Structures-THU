#include<stdio.h>
#include<string.h>
int Zone(int *a , int *b , int x , int y , int lo , int hi);//声明函数Zone，参数包括数组a，b，点坐标x，y，查找区间lo，hi 
int main()
{
	int n , m , i , lo , hi;
	scanf("%d %d\n" , &n , &m);
	int a[n] , b[n] , x[m] , y[m] , zone[m]; //声明数组：a，b用于存直线截距；x，y用于存点坐标；zone用于记录点的所在区域 
	
	for(i = 0 ; i < n ; i ++) scanf("%d %d\n" , &a[i] , &b[i]);
	for(i = 0 ; i < m - 1 ; i ++) scanf("%d %d\n" , &x[i] , &y[i]);
	scanf("%d %d" , &x[m - 1] , &y[m - 1]);//输入数据 
	
	for(i = 0 ; i < m ; i ++) zone[i] = Zone(a , b , x[i] , y[i] , 0 , n);//循环m次，利用Zone函数确定各点所在区域 
	
	for(i = 0 ; i < m - 1 ; i ++) printf("%d\n" , zone[i]);
	printf("%d" , zone[m - 1]);//输出 
	
}
int Zone(int *a , int *b , int x , int y , int lo , int hi)
{
	int mi = (lo + hi) >> 1;//查找区间的中点 
	if((lo < hi) != 1) return mi;//lo非减，hi非增，若不再严格小于则说明已找到所在区域 
	else 
	{
		long long int criterion;//声明long long int型的判据变量 
	    criterion = (long long int)a[mi] * (long long int)y + (long long int)b[mi] * (long long int)x - (long long int)a[mi] * (long long int)b[mi];
	    if(criterion == 0) return mi + 1;//落在线上则返回右侧区域 
	    else if (criterion > 0) return Zone(a , b , x , y , mi + 1 , hi);//落在线的上方则修改lo为mi+1继续查找 
	    else if (criterion < 0) return Zone(a , b , x , y , lo , mi);//落在线的下方则修改hi为mi继续查找 
	}
}
