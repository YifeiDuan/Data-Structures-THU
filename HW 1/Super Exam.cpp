#include<stdio.h>
#include<string.h>
struct student
{
	int ID;
	struct student *nNext;
	struct student *sNext;
};//����ṹ����student������ѧ�ź�����ָ�루�ֱ�ָ��˳��ʱ�����һ��ѧ���� 
int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);//��������n,m 
	struct student *examinees = new struct student[n];//�����ṹ���� 
	struct student *last , *next; //�ṹ��ָ�룬�����ڡ������������б��ĳһλ�õ�ǰ������λ�� 
	
	int i , j;
	for(i = 0 ; i < n ; i ++) scanf("%d" , &examinees[i].ID);//¼��ѧ�Ŵ���ṹ������ 
	
	examinees[0].nNext = &examinees[0]; 
	examinees[0].sNext = &examinees[0];//ģ���һ��ѧ����������ʱ��˳��ʱ�����һ�˾�Ϊ�Լ� 
	 
	for(i = 0 ; i < n - 1 ; i ++)//n-1��ѭ��ģ�����ÿ��ѧ���������� 
	{
		last = &examinees[i];//���ڴ�ǰһ��ѧ����������lastָ��ָ��ǰһ��������ѧ�� 
		for(j = 0 ; j < m - 1 ; j ++)//Ҫ��ʱ���߹�m�ˣ���ȥǰһ��������֮�⻹��m-1�� 
		{
			last = last->nNext; 
			next = last->nNext;//��ǰҪ������ѧ��λ��ÿ�ƶ�һ�£���ʱ���ﾳ�µġ�ǰһλ�á�Ҳ��ʱ���ƶ�һ��������һλ�á����µġ�ǰһλ�á�����ʱ���� 
		}//��ѭ�����������ʾ���߹�m���ˣ�last��nextָ�����ڷֱ�ָ��Ҫ����λ�õ�ǰ������ 
		examinees[i + 1].nNext = next;
		examinees[i + 1].sNext = last;//�������ṹ���ڵ�����ָ��ֱ�ֵΪlast��next 
		last->nNext = &examinees[i + 1];
		next->sNext = &examinees[i + 1];//�ı�ǰ�������˸��Ե�һ���ڲ�ָ��ָ��������������� 
	}
	
	next = &examinees[n - 1];//�������׼����next������ȡ��Ϣ�Ķ��󣬸���ֵ������������� 
	for(i = 1 ; i <= n - 1 ; i ++)//���ýṹ����sNextָ�룬˳�ζ�ȡѧ�Ų���� 
	{
		printf("%d " , next->ID);
		next = next->sNext;
	}
	printf("%d" , next->ID);
} 
