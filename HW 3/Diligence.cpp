#include<stdio.h>
#include<string.h>

struct record
{
	char name[9];
	int times;
}students[30000]; //�ṹ�������¼ѧ�����ֺʹ��� 

int max; //���ˢ���� 
char best[9]; //���ڷܵ�ѧ������ 

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
		for(j = 0 ; j < strlen(input) ; j ++) key = key * 9 + (int)input[j] - 96; //���ö���ʽ�������ַ���ת��Ϊ���͹ؼ��� 
		int index = key % 20011; //ģ��ȡΪ�洢���� 
		while((students[index].times != 0)&&(strcmp(input , students[index].name) != 0)) index ++; //�����ͬ�������˳���Ӻ��ҿ�λ 
		strcpy(students[index].name , input);
		students[index].times ++;
	}
	
	max = 0;
	for(i = 0 ; i < 30000 ; i ++) //�����洢������Ѱ�Ҵ��������� 
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
