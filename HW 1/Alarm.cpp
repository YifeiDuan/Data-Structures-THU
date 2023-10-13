#include<stdio.h>
#include<string.h>
int Zone(int *a , int *b , int x , int y , int lo , int hi);//��������Zone��������������a��b��������x��y����������lo��hi 
int main()
{
	int n , m , i , lo , hi;
	scanf("%d %d\n" , &n , &m);
	int a[n] , b[n] , x[m] , y[m] , zone[m]; //�������飺a��b���ڴ�ֱ�߽ؾࣻx��y���ڴ�����ꣻzone���ڼ�¼����������� 
	
	for(i = 0 ; i < n ; i ++) scanf("%d %d\n" , &a[i] , &b[i]);
	for(i = 0 ; i < m - 1 ; i ++) scanf("%d %d\n" , &x[i] , &y[i]);
	scanf("%d %d" , &x[m - 1] , &y[m - 1]);//�������� 
	
	for(i = 0 ; i < m ; i ++) zone[i] = Zone(a , b , x[i] , y[i] , 0 , n);//ѭ��m�Σ�����Zone����ȷ�������������� 
	
	for(i = 0 ; i < m - 1 ; i ++) printf("%d\n" , zone[i]);
	printf("%d" , zone[m - 1]);//��� 
	
}
int Zone(int *a , int *b , int x , int y , int lo , int hi)
{
	int mi = (lo + hi) >> 1;//����������е� 
	if((lo < hi) != 1) return mi;//lo�Ǽ���hi�������������ϸ�С����˵�����ҵ��������� 
	else 
	{
		long long int criterion;//����long long int�͵��оݱ��� 
	    criterion = (long long int)a[mi] * (long long int)y + (long long int)b[mi] * (long long int)x - (long long int)a[mi] * (long long int)b[mi];
	    if(criterion == 0) return mi + 1;//���������򷵻��Ҳ����� 
	    else if (criterion > 0) return Zone(a , b , x , y , mi + 1 , hi);//�����ߵ��Ϸ����޸�loΪmi+1�������� 
	    else if (criterion < 0) return Zone(a , b , x , y , lo , mi);//�����ߵ��·����޸�hiΪmi�������� 
	}
}
