#include<stdio.h>
#include<string.h>
char team(int n , int *mark , int k , int *a , int *b , int *c);
//��������ȷ����Ա����ĺ���team������������Ա����n���������mark����Ա���k��������������ϲ�����������a,b,c 

int main()
{
	int n , k , i;
	scanf("%d", &n);
	int a[n] , b[n] , c[n] , mark[n + 1];
	for(i = 0 ; i < n ; i ++) scanf("%d" , &a[i]);
	for(i = 0 ; i < n ; i ++) scanf("%d" , &b[i]);
	for(i = 0 ; i < n ; i ++) scanf("%d" , &c[i]);
	scanf("%d", &k);
	//¼��������� 
	
	memset(mark , 0 , n + 1);//�����ڱ�Ƕ�Ա�Ƿ�ѡ�е�����mark��Ԫ�ظ���ֵΪ0 
	printf("%c" , team(n , mark , k , a , b , c));//���ݲ������ú���team�õ��𰸲���� 
	
 } 
 char team(int n , int *mark , int k , int *a , int *b , int *c)
 {
 	int A = 0 , B = 0 , C = 0 , i;//��������A,B,C�ֱ����ڼ�¼������������Ķ�Ա���Լ�ϲ�ö��е�˳λ��i��ʾ��i��ѡ��Ա��һ���� 
 	char result;//��������ֵ���� 
 	
 	for(i = 0 ; i < n ; i ++) //��ѭ�����ģ��ÿ��ѡ���Ա�Ĺ��� 
 	{
 		if(i % 3 == 0)//ģ3��0��˵���ô�ѡ��Ա������A������ɣ�B,Cͬ�� 
 		{
 			while(mark[a[A]] == 1) A++;//����ϲ��˳λ���ѱ�Ǳ�ѡ�ߵĶ�Ա��������������ѡ˳λA��֮�������� 
 			if(a[A] == k)
 			{
 				result = 'A';
 				break;
			 }//���δ��ѡ�ߵ����˳λ��ǡ����k����ԭ�������ȷ������¼������ѭ�� 
 			else mark[a[A]] = 1;//���򣬽���˳λ��Ա���ѡ�У������β�����ѭ������ 
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
	return result;//���ؽ�� 
 }
