#include<stdio.h>
#include<string.h>
struct vertex
{
	int indegree; //��� 
	int outdegree; //���� 
	int *next; //���ȼ������к�̣� 
	int *edge; //��¼�ӵ�ǰ����ָ�����̵Ĳ��
	int max; //��¼�Ӹó����ߵ�����ȵ�ĸ�·���������������
	int imax; //��¼������������Ӧ�ĺ�̽ڵ� 
}; 

int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	
	struct vertex *graph = new struct vertex[n + 1]; //����ͼ
	
	int i , j;
	for(i = 0 ; i <= n ; i ++)
	{
		graph[i].indegree = 0;
		graph[i].outdegree = 0;
		graph[i].next = new int[101];
		graph[i].edge = new int[101];
		graph[i].max = 0;
		graph[i].imax = -1; 
	}  //ͼ�и����еĸ�����Ϣ��ʼ�� 
	
	int start , end , price; //ÿ������ߵ���㡢�յ㡢��� 
	for(i = 1 ; i <= m ; i ++)
	{
		if(i == m) scanf("%d %d %d" , &start , &end , &price);
		else scanf("%d %d %d\n" , &start , &end , &price);
		
		graph[start].outdegree += 1; //������+1
		if(graph[start].outdegree + 1 > 101) //������ȴ�С������ʼ�趨����������Ҫ�������� 
		{
			int *p = new int[graph[start].outdegree];
			int *q = new int[graph[start].outdegree];
			for(j = 0 ; j <= graph[start].outdegree - 1 ; j ++)
			{
				p[j] = graph[start].next[j];
				q[j] = graph[start].edge[j];
			}
			delete[] graph[start].next;
			delete[] graph[start].edge;
			
			graph[start].next = new int[graph[start].outdegree + 1];
			graph[start].edge = new int[graph[start].outdegree + 1];
			for(j = 0 ; j <= graph[start].outdegree - 1 ; j ++)
			{
				graph[start].next[j] = p[j];
				graph[start].edge[j] = q[j];
			}
			delete[] p;
			delete[] q;
		}
		else n += 0;
		
		graph[start].next[graph[start].outdegree] = end; //�յ������ĵڳ��ȸ���� 
		graph[start].edge[graph[start].outdegree] = price; //��¼��Ӧ�ߵĲ�� 
		graph[end].indegree += 1; //�յ����+1
	}
	
	//����Ϊ�������� 
	int *stack = new int[n + 1]; //��Ϊջʹ�õ�����
	int top = 0; //ջ�� 
	int *queue = new int[n + 1]; //��Ϊ����ʹ�á��������������������
	int tail = 0; //��β 
	for(i = 1 ; i <= n ; i ++)
	{
		if(graph[i].indegree == 0)
		{
			top ++;
			stack[top] = i;
		} 
		else continue;
	} //��ʼ������ȵ���ջ 
	while(top > 0) //��ջ��Ϊ��ʱ 
	{
		tail ++;
		queue[tail] = stack[top]; //ջ��ת���β 
		int current = stack[top]; //��¼�ýڵ���
		stack[top] = 0;
		top --; //ջ��ǰ�� 
		for(i = 1 ; i <= graph[current].outdegree ; i ++)
		{
			int successor = graph[current].next[i]; //successorΪ��ǰ�鿴�ĺ�̽ڵ� 
			if(graph[successor].indegree == 1)
			{
				top ++;
				stack[top] = successor;
			}
			else top += 0;
			
			graph[successor].indegree -= 1; 
		}
	}
	
	
	//����Ϊ��̬�滮��ȡ��������������Ϣ 
	int earning; //���ڼ���������� 
	for(i = n ; i > 0 ; i --) //��������ĩβ��ʼ��ǰ���Ƽ�¼�������������� 
	{
		int index = queue[i]; 
		if(graph[index].outdegree == 0) continue; //����ȵ����Ϣ���ʼ��ֵ��ͬ�����ظ��£�ֱ�Ӽ���ѭ�� 
		else
		{
			for(j = 1 ; j <= graph[index].outdegree ; j ++)
			{
				earning = graph[index].edge[j] + graph[graph[index].next[j]].max; //���ʱ������Ӧ������=������Ȩ��+��̵�������� 
				if(earning > graph[index].max) //����������ȴ�ǰ��¼����������������� 
				{
					graph[index].max = earning;
					graph[index].imax = graph[index].next[j];
				}
				else if(earning == graph[index].max)//�����ȣ���¼�ֵ����С�ĺ�� 
				{
					if(graph[index].next[j] < graph[index].imax) graph[index].imax = graph[index].next[j];
					else graph[index].imax += 0;
				}
				else continue;
			} 
		}
	}  
	
	//����Ϊ�ҵ�������������·���ϵĸ��ڵ� 
	int Max = 0; //���������������Ǹ�
	int MaxStart = 0; //��¼�������·������� 
	for(i = 1 ; i <= n ; i ++) //�����е���Ѱ����� 
	{
		if(graph[queue[i]].max > Max)
		{
			Max = graph[queue[i]].max;
			MaxStart = queue[i];
		} 
		else if(graph[queue[i]].max == Max)
		{
			if(graph[queue[i]].imax < MaxStart) MaxStart = queue[i];
			else MaxStart += 0;
		}
		else continue;
	} 
	j = MaxStart;
	while(graph[j].outdegree > 0)
	{
		printf("%d " , j);
		j = graph[j].imax;
	} 
	printf("%d" , j);
	
} 


