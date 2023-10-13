#include<stdio.h>
#include<string.h>
struct vertex
{
	int indegree; //��� 
	int outdegree; //���� 
	int next[100001]; //��¼���е�ǰ���й���������ߵ��յ㣨��̣� 
	int edge[100001]; //��¼�ӵ�ǰ����ָ������е�����߶�Ӧ�Ĳ�� 
}; 

int path[100000]; //��¼������������·�� 
int max; //��¼Ŀǰ����·�ߵ����� 

void FindPath(struct vertex *graph , int city , int *path , int length , int earning); 
int main()
{
	int n , m;
	scanf("%d %d\n" , &n , &m);
	
	struct vertex *graph = new struct vertex[n + 1];
	
	int i , j;
	for(i = 0 ; i <= n ; i ++)
	{
		graph[i].indegree = 0;
		graph[i].outdegree = 0;
		/*for(j = 0 ; j <= 100000 ; j ++)
		{
			graph[i].next[j] = 0;
			graph[i].edge[j] = 0;
		}*/
	}  //ͼ�и����еĸ�����Ϣ����ֵ0
	
	int start , end , price; //ÿ������ߵ���㡢�յ㡢��� 
	for(i = 1 ; i <= m ; i ++)
	{
		if(i == m) scanf("%d %d %d" , &start , &end , &price);
		else scanf("%d %d %d\n" , &start , &end , &price);
		
		graph[start].outdegree += 1; //������+1 
		graph[start].next[graph[start].outdegree] = end; //�յ������ĵڳ��ȸ���� 
		graph[start].edge[end] = price; //��¼��Ӧ�ߵĲ�� 
		graph[end].indegree += 1; //�յ����+1 
	}
	
	for(i = 0 ; i < 100000 ; i ++)
	{
		path[i] = 0;
	}
	max = 0;
	for(i = 1 ; i <= n ; i ++)
	{
		if(graph[i].indegree == 0) FindPath(graph , i , path , 0 , 0);
	} 
	
	printf("%d" , max); 
} 

void FindPath(struct vertex *graph , int city , int *path , int length , int earning)
{
	path[length] = city; //�ѵ�ǰ���м���·�� 
	
	int k;
	if(graph[city].outdegree == 0) //�����ǰ����û�к�̣���������������ҵ�һ��·�ߣ���ʼ��֮ǰ�����·�����Ƚϴ��� 
	{
		if(earning > max) //����·��׬Ǯ���� 
		{
			max = earning; //������������
		}
		else max += 0;
		
		path[length] = 0; //��·�������һ�����㣬Ȼ�󷵻���һ�� 
		return; 
	}
	else //�����ǰ�����к��
	{
		for(k = 1 ; k <= graph[city].outdegree ; k ++) //���ν����к����Ϊ·������һ����еݹ� 
		{
			int nextcity = graph[city].next[k];
			FindPath(graph , nextcity , path , length + 1 , earning + graph[city].edge[nextcity]);
		}
		
		path[length] = 0; //��·�������һ�����㣬Ȼ�󷵻���һ��
		return; 
	} 
}
