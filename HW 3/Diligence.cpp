#include<stdio.h>
#include<string.h>

struct record
{
	char name[9];
	int times;
}students[30000]; //结构体数组记录学生名字和次数 

int max; //最大刷题数 
char best[9]; //最勤奋的学生名字 

int main()
{
	int n;	
	scanf("%d\n" , &n);
	
	int i , j;
	char input[9];
	for(i = 1 ; i <= n ; i ++)
	{
		scanf("%s" , &input);
		int key = 0;
		for(j = 0 ; j < strlen(input) ; j ++) key = key * 9 + (int)input[j] - 96; //利用多项式方法将字符串转化为整型关键码 
		int index = key % 20011; //模余取为存储索引 
		while((students[index].times != 0)&&(strcmp(input , students[index].name) != 0)) index ++; //如果有同余情况则顺次延后找空位 
		strcpy(students[index].name , input);
		students[index].times ++;
	}
	
	max = 0;
	for(i = 0 ; i < 30000 ; i ++) //遍历存储的数组寻找次数最多的人 
	{
		if(students[i].times > max) 
		{
			max = students[i].times;
			strcpy(best , students[i].name);
		}
	}
	printf("%s %d" , best , max);
	
	return 0;
}
