#include<stdio.h>
#include<string.h>
struct student
{
	int ID;
	struct student *nNext;
	struct student *sNext;
};//定义结构类型student，包含学号和两个指针（分别指向顺逆时针的下一名学生） 
int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);//输入数据n,m 
	struct student *examinees = new struct student[n];//创建结构数组 
	struct student *last , *next; //结构型指针，用于在“落座”过程中标记某一位置的前后两个位置 
	
	int i , j;
	for(i = 0 ; i < n ; i ++) scanf("%d" , &examinees[i].ID);//录入学号存入结构体数组 
	
	examinees[0].nNext = &examinees[0]; 
	examinees[0].sNext = &examinees[0];//模拟第一名学生落座，此时其顺逆时针的下一人均为自己 
	 
	for(i = 0 ; i < n - 1 ; i ++)//n-1次循环模拟后续每名学生依次落座 
	{
		last = &examinees[i];//由于从前一名学生出发，故last指针指向前一名落座的学生 
		for(j = 0 ; j < m - 1 ; j ++)//要逆时针走过m人，除去前一名落座者之外还有m-1人 
		{
			last = last->nNext; 
			next = last->nNext;//当前要落座的学生位置每移动一下，逆时针语境下的“前一位置”也逆时针移动一名，“后一位置”是新的“前一位置”的逆时针后继 
		}//内循环结束后则表示已走过m个人，last和next指针现在分别指向要落座位置的前后两人 
		examinees[i + 1].nNext = next;
		examinees[i + 1].sNext = last;//落座，结构体内的两个指针分别赋值为last和next 
		last->nNext = &examinees[i + 1];
		next->sNext = &examinees[i + 1];//改变前后两个人各自的一个内部指针指向新完成落座的人 
	}
	
	next = &examinees[n - 1];//在输出中准备用next表征读取信息的对象，赋初值给最后落座的人 
	for(i = 1 ; i <= n - 1 ; i ++)//利用结构体内sNext指针，顺次读取学号并输出 
	{
		printf("%d " , next->ID);
		next = next->sNext;
	}
	printf("%d" , next->ID);
} 
