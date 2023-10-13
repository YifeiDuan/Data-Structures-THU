#include<stdio.h>
#include<string.h>
char team(int n , int *mark , int k , int *a , int *b , int *c);
//声明用于确定队员队伍的函数team，参数包括队员总数n，标记数组mark，队员编号k，三个表征教练喜好排序的数组a,b,c 

int main()
{
	int n , k , i;
	scanf("%d", &n);
	int a[n] , b[n] , c[n] , mark[n + 1];
	for(i = 0 ; i < n ; i ++) scanf("%d" , &a[i]);
	for(i = 0 ; i < n ; i ++) scanf("%d" , &b[i]);
	for(i = 0 ; i < n ; i ++) scanf("%d" , &c[i]);
	scanf("%d", &k);
	//录入各种数据 
	
	memset(mark , 0 , n + 1);//将用于标记队员是否被选中的数组mark各元素赋初值为0 
	printf("%c" , team(n , mark , k , a , b , c));//传递参数，用函数team得到答案并输出 
	
 } 
 char team(int n , int *mark , int k , int *a , int *b , int *c)
 {
 	int A = 0 , B = 0 , C = 0 , i;//声明变量A,B,C分别用于记录三个教练考察的队员在自己喜好度中的顺位，i表示第i次选队员这一操作 
 	char result;//声明返回值变量 
 	
 	for(i = 0 ; i < n ; i ++) //用循环语句模拟每次选择队员的过程 
 	{
 		if(i % 3 == 0)//模3余0则说明该次选队员操作由A教练完成，B,C同理 
 		{
 			while(mark[a[A]] == 1) A++;//对于喜好顺位中已标记被选走的队员依次跳过，将备选顺位A随之依次增加 
 			if(a[A] == k)
 			{
 				result = 'A';
 				break;
			 }//如果未被选走的最高顺位者恰好是k，则原问题答案已确定，记录并跳出循环 
 			else mark[a[A]] = 1;//否则，将该顺位队员标记选中，完成这次操作，循环继续 
		}
		else if(i % 3 == 1)
 		{
 			while(mark[b[B]] == 1) B++;
 			if(b[B] == k)
 			{
 				result = 'B';
 				break;
			 }
 			else mark[b[B]] = 1;
		}
		else if(i % 3 == 2)
 		{
 			while(mark[c[C]] == 1) C++;
 			if(c[C] == k)
 			{
 				result = 'C';
 				break;
			 }
 			else mark[c[C]] = 1;
		}
	}
	return result;//返回结果 
 }
